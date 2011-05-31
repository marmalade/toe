#pragma once

#include <toeComponent.h>
#include <Box2D/Box2D.h>

class b2Body;
namespace TinyOpenEngine
{
	class CtoeBox2DWorld;
	class CtoeBox2DBody : public CtoeComponent
	{
	protected:
		b2Body* body;
		bool dynamicBody;
		/// The linear velocity of the body's origin in world co-ordinates.
		b2Vec2 linearVelocity;
		/// The angular velocity of the body.
		float angularVelocity;
		/// Linear damping is use to reduce the linear velocity. The damping parameter
		/// can be larger than 1.0f but the damping effect becomes sensitive to the
		/// time step when the damping parameter is large.
		float32 linearDamping;

		/// Angular damping is use to reduce the angular velocity. The damping parameter
		/// can be larger than 1.0f but the damping effect becomes sensitive to the
		/// time step when the damping parameter is large.
		float32 angularDamping;

		/// Set this flag to false if this body should never fall asleep. Note that
		/// this increases CPU usage.
		bool allowSleep;

		/// Is this body initially awake or sleeping?
		bool awake;

		/// Should this body be prevented from rotating? Useful for characters.
		bool fixedRotation;

		/// Is this a fast moving body that should be prevented from tunneling through
		/// other moving bodies? Note that all bodies are prevented from tunneling through
		/// kinematic and static bodies. This setting is only considered on dynamic bodies.
		/// @warning You should use this flag sparingly since it increases processing time.
		bool bullet;

		/// Does this body start out active?
		bool active;
		/// Scale the gravity applied to this body.
		float32 gravityScale;
	public:
		//Constructor
		CtoeBox2DBody();
		//Desctructor
		virtual ~CtoeBox2DBody();

		virtual void OnAttachedToSubsytem(CtoeSubsystem* s);
		virtual void OnDetachedFromSubsytem(CtoeSubsystem* s);

		virtual void DeleteBody();
		virtual void CreateBody(CtoeBox2DWorld*);
		virtual void CreateShape(b2Body* body);
		//Update entity transform
		virtual void UpdateEntityTransform();

		CtoeBox2DWorld* GetBox2DWorld() const;

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();
#ifdef IW_BUILD_RESOURCES

		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}