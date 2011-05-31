#pragma once

#include <toeSubsystemItems.h>
#include <toeComponent.h>
#include <toeSelfRenderedComponent.h>

namespace TinyOpenEngine
{
	class Ctoe3DRenderContext: public CtoeRenderContext
	{
	protected:
		CIwMat viewMatrix;

	public:
		void SetCameraEntity(CtoeEntity* e);
	};

	class Ctoe3DScene : public TtoeSubsystem<CtoeSelfRenderedComponent>
	{
	protected:
		CtoeEntityWeakPointer cameraEntity;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(Ctoe3DScene);
		//Constructor
		Ctoe3DScene();
		//Desctructor
		virtual ~Ctoe3DScene();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();

		virtual void Render();
	};
}