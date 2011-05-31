#pragma once

#include <IwArray.h>

namespace TinyOpenEngine
{
	class ItoeScriptingSubsystem;
	class CtoeScriptableClassDeclaration;

	class CtoeScriptableMethodDeclaration
	{
		const char* m_name;
	public:
		CtoeScriptableMethodDeclaration(const char* name):m_name(name) {}
		virtual ~CtoeScriptableMethodDeclaration() {};
		inline const char* GetMethodName() {return m_name;};
		virtual void Call(ItoeScriptingSubsystem*,CtoeScriptableClassDeclaration*,void*)=0;
		virtual bool IsStatic() const {return false;}
	};

	class CtoeScriptableClassDeclaration
	{
	protected:
		CIwArray<CtoeScriptableMethodDeclaration*> m_methods;
	public:
		virtual void Close() { for (CIwArray<CtoeScriptableMethodDeclaration*>::iterator i=m_methods.begin(); i!=m_methods.end(); ++i) delete *i; m_methods.clear_optimised(); };
		virtual ~CtoeScriptableClassDeclaration() {Close();}
		virtual const char* GetClassName() =0;
		virtual void* CreateInstance() =0;
		virtual void DestroyInstance(void*) =0;
		virtual const char* ToString(void* t)=0;
		virtual int GetMethodsCount() { return m_methods.size(); }
		virtual CtoeScriptableMethodDeclaration* GetMethod(int i) { return m_methods[i]; }
	};

	class ItoeScriptingSubsystem
	{
	public:
		virtual ~ItoeScriptingSubsystem();

		virtual void Eval(const char*s, void* instance, CtoeScriptableClassDeclaration*c)=0;

		virtual void RegisterClass(CtoeScriptableClassDeclaration*)=0;

		virtual void Return()=0;
		virtual void ReturnNil()=0;
		virtual void Return(int i)=0;
		virtual void Return(float i)=0;
		virtual void Return(const char*)=0;
		virtual void Return(bool)=0;
		virtual void Return(void*,CtoeScriptableClassDeclaration*)=0;

		virtual int PopArgInt()=0;
		virtual float PopArgFloat()=0;
		virtual const char* PopArgStr()=0;
		virtual bool PopArgBool()=0;
		virtual void* PopArgClass(CtoeScriptableClassDeclaration*)=0;
	};
}
#include "toeScriptingBinds.h"
