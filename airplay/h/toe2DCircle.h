#pragma once

#include <toeComponent.h>
#include <toeSelfRenderedComponent.h>
namespace TinyOpenEngine
{
	class Ctoe2DCircle : public CtoeSelfRenderedComponent
	{
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(Ctoe2DCircle);
		//Constructor
		Ctoe2DCircle();
		//Desctructor
		virtual ~Ctoe2DCircle();

		virtual void Render(CtoeRenderContext*);
	};
}