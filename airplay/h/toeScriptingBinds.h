#pragma once

#include <string>

namespace TinyOpenEngine
{
	namespace ScriptTraits
	{
		template <class T> class StripPointer { public: typedef T STRIPPED; };
		template <class T> class StripPointer<T*> { public: typedef T STRIPPED; };

		CtoeScriptableClassDeclaration* GetManagedInstanceClassDescription(CIwManaged* t);
		template <class T> inline CtoeScriptableClassDeclaration* GetInstanceClassDescription(T*t) { return t->GetInstanceClassDescription(); }
		template <> inline CtoeScriptableClassDeclaration* GetInstanceClassDescription<CIwManaged>(CIwManaged*t) { return GetManagedInstanceClassDescription(t); }

		template <typename T> inline T FetchArgument(ItoeScriptingSubsystem* system) { return system->PopArgClass(StripPointer<T>::STRIPPED::GetClassDescription()); };
		template <> inline int FetchArgument<int>(ItoeScriptingSubsystem* system) { return system->PopArgInt(); };
		template <> inline float FetchArgument<float>(ItoeScriptingSubsystem* system) { return system->PopArgFloat(); };
		template <> inline double FetchArgument<double>(ItoeScriptingSubsystem* system) { return system->PopArgFloat(); };
		template <> inline const char* FetchArgument<const char *>(ItoeScriptingSubsystem* system) { return system->PopArgStr(); };
		template <> inline bool FetchArgument<bool>(ItoeScriptingSubsystem* system) { return system->PopArgBool(); };

		template <class T> inline void PushResult(ItoeScriptingSubsystem* system, T t) { system->Return(t); };
		template <> inline void PushResult<std::string>(ItoeScriptingSubsystem* system, std::string t) { system->Return(t.c_str()); };
		template <class PTR> inline void PushResult(ItoeScriptingSubsystem* system, PTR* t)
		{
			if (t)
				system->Return(t, GetInstanceClassDescription(t));
			else
				system->ReturnNil();
		};
		template <> inline void PushResult<const char>(ItoeScriptingSubsystem* system, const char* t)
		{
			system->Return(t);
		};
		template <typename R> class NoArgFunction: public CtoeScriptableMethodDeclaration
		{
		public:
			typedef R(* METHOD)();
		protected:
			METHOD m;
		public:
			virtual bool IsStatic() const {return true;}
			NoArgFunction(const char* name, METHOD mm):CtoeScriptableMethodDeclaration(name),m(mm) {}
			R MakeCall(ItoeScriptingSubsystem* system, CtoeScriptableClassDeclaration* cls, void* instance)
			{
				return m();
			}
		};
		template <typename R, typename A> class OneArgFunction: public CtoeScriptableMethodDeclaration
		{
		public:
			typedef R(* METHOD)(A);
		protected:
			METHOD m;
		public:
			virtual bool IsStatic() const {return true;}
			OneArgFunction(const char* name, METHOD mm):CtoeScriptableMethodDeclaration(name),m(mm) {}
			R MakeCall(ItoeScriptingSubsystem* system, CtoeScriptableClassDeclaration* cls, void* instance)
			{
				return m(FetchArgument<A>(system));
			}
		};
		template <typename R, typename A1, typename A2> class TwoArgFunction: public CtoeScriptableMethodDeclaration
		{
		public:
			typedef R(* METHOD)(A1,A2);
		protected:
			METHOD m;
		public:
			virtual bool IsStatic() const {return true;}
			TwoArgFunction(const char* name, METHOD mm):CtoeScriptableMethodDeclaration(name),m(mm) {}
			R MakeCall(ItoeScriptingSubsystem* system, CtoeScriptableClassDeclaration* cls, void* instance)
			{
				A1 a1 = FetchArgument<A1>(system);
				return m(a1, FetchArgument<A2>(system));
			}
		};
		template <class T, class R, typename mmm> class NoArgsMethod: public CtoeScriptableMethodDeclaration
		{
		public:
			typedef mmm METHOD;
			//typedef R (T::* METHOD)();
		protected:
			METHOD m;
		public:
			NoArgsMethod(const char* name, METHOD mm):CtoeScriptableMethodDeclaration(name),m(mm) {}
			R MakeCall(ItoeScriptingSubsystem* system, CtoeScriptableClassDeclaration* cls, void* instance)
			{
				T* i = ((T*)instance);
				return (i->*m)();
			}
		};
		template <class T, class R, typename A, typename mmm> class OneArgsMethod: public CtoeScriptableMethodDeclaration
		{
		public:
			typedef mmm METHOD;
		protected:
			METHOD m;
		public:
			OneArgsMethod(const char* name, METHOD mm):CtoeScriptableMethodDeclaration(name),m(mm) {}
			R MakeCall(ItoeScriptingSubsystem* system, CtoeScriptableClassDeclaration* cls, void* instance)
			{
				T* i = ((T*)instance);
				return (i->*m)(FetchArgument<A>(system));
			}
		};
		template <class R, class Caller> class MethodBase: public Caller
		{
		public:
			MethodBase(const char* name, typename Caller::METHOD m):Caller(name,m) {}
			virtual void Call(ItoeScriptingSubsystem* system, CtoeScriptableClassDeclaration* cls, void* instance)
			{
				PushResult(system, Caller::MakeCall(system,cls,instance));
			}
		};
		template <class Caller> class MethodBase<void,Caller>: public Caller
		{
		public:
			MethodBase(const char* name, typename Caller::METHOD m):Caller(name,m) {}
			virtual void Call(ItoeScriptingSubsystem* system, CtoeScriptableClassDeclaration* cls, void* instance)
			{
				Caller::MakeCall(system,cls,instance);
				system->Return();
			}
		};
		template <typename R> inline CtoeScriptableMethodDeclaration* Method(const char* name, R (*fn) ())
		{
			return new MethodBase<R,NoArgFunction<R> >(name,fn);
		};
		template <typename R,typename A> inline CtoeScriptableMethodDeclaration* Method(const char* name, R (*fn) (A))
		{
			return new MethodBase<R,OneArgFunction<R,A> >(name,fn);
		};
		template <typename R,typename A1,typename A2> inline CtoeScriptableMethodDeclaration* Method(const char* name, R (*fn) (A1,A2))
		{
			return new MethodBase<R,TwoArgFunction<R,A1,A2> >(name,fn);
		};
		template <class T, typename R> inline CtoeScriptableMethodDeclaration* Method(const char* name, R (T::*fn) ())
		{
			return new MethodBase<R,NoArgsMethod<T,R,R (T::*) ()> >(name,fn);
		};
		template <class T, typename R> inline CtoeScriptableMethodDeclaration* Method(const char* name, R (T::*fn)  () const)
		{
			return new MethodBase<R,NoArgsMethod<T,R,R (T::*)  () const> >(name,fn);
		};
		template <class T, typename R,typename A> inline CtoeScriptableMethodDeclaration* Method(const char* name, R (T::*fn) (A))
		{
			return new MethodBase<R,OneArgsMethod<T,R,A,R (T::*) (A)> >(name,fn);
		};
		template <class T, typename R,typename A> inline CtoeScriptableMethodDeclaration* Method(const char* name, R (T::*fn)  (A) const)
		{
			return new MethodBase<R,OneArgsMethod<T,R,A,R (T::*)  (A) const> >(name,fn);
		};
	}
	template <class T> class TtoeScriptableMethodDeclaration: public CtoeScriptableMethodDeclaration
	{
		void (T::*m_fn) ();
	public:
		TtoeScriptableMethodDeclaration(const char* name,void (T::*fn) ()):CtoeScriptableMethodDeclaration(name),m_fn(fn) {}
		virtual void Call(ItoeScriptingSubsystem* s,CtoeScriptableClassDeclaration*c,void* o) { (((T*)o)->*m_fn)(); }
	};

	template <class T, typename R> class TtoeScriptableMethodDeclarationR: public CtoeScriptableMethodDeclaration
	{
		R (T::*m_fn) ();
	public:
		TtoeScriptableMethodDeclarationR(const char* name,R (T::*fn) ()):CtoeScriptableMethodDeclaration(name),m_fn(fn) {}
		virtual void Call(ItoeScriptingSubsystem* s,CtoeScriptableClassDeclaration*c,void* o) { s->Return( (((T*)o)->*m_fn)() ); }
	};

		template <class T> class TtoeScriptableClassDeclaration: public CtoeScriptableClassDeclaration
	{
		const char* m_name;
	public:
		TtoeScriptableClassDeclaration(const char* name, ...);
		virtual ~TtoeScriptableClassDeclaration() {}
		virtual const char* GetClassName() {return m_name;}

		virtual void* CreateInstance() {return new T();}
		virtual void DestroyInstance(void* t) { delete (T*)t;}
		virtual const char* ToString(void* t) { return GetClassName(); }

		//virtual int GetMethodsCount() { return 0; }
		//virtual CtoeScriptableMethodDeclaration* GetMethod(int i) { return 0; }
		//static CtoeScriptableMethodDeclaration* M( void (T::*ptr)() ) { return 0;}
	};

	template <class T> TtoeScriptableClassDeclaration<T>::TtoeScriptableClassDeclaration(const char* name, ...)
	{
		m_name = name;
		va_list vl;
		va_start( vl, name );
		for (;;)
		{
			CtoeScriptableMethodDeclaration* arg = va_arg( vl, CtoeScriptableMethodDeclaration*);
			if (!arg)
				break;
			m_methods.push_back(arg);
		}
		va_end( vl );
	}
}