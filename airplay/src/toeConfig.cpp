#include "toeConfig.h"
#include "pugixml.hpp"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	const char* toeConfigFilePath = "ram://app.config";
	pugi::xml_document* toeConfigDocument=0;
	pugi::xml_node toeGetConfigNodeText(const char* name)
	{
		pugi::xml_node configuration = toeConfigDocument->child("configuration");
		if (!configuration) configuration = toeConfigDocument->append_child("configuration");
		pugi::xml_node appSettings = configuration.child("appSettings");
		if (!appSettings) appSettings = configuration.append_child("appSettings");
		pugi::xml_node item = appSettings.child(name);
		if (!item)
		{
			item = appSettings.append_child(name);
		}
		pugi::xml_node text = item.first_child();
		if (!text) text = item.append_child(pugi::node_pcdata);
		return text;
	}
}
//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeConfig::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeConfig> d ("CtoeConfig",
			ScriptTraits::Method("GetInteger", &CtoeConfig::GetInteger),
			ScriptTraits::Method("GetFloat", &CtoeConfig::GetFloat),
			ScriptTraits::Method("GetString", &CtoeConfig::GetString),
			ScriptTraits::Method("SetInteger", &CtoeConfig::SetInteger),
			ScriptTraits::Method("SetFloat", &CtoeConfig::SetFloat),
			ScriptTraits::Method("SetString", &CtoeConfig::SetString),
			0);
	return &d;
}
void CtoeConfig::SetInteger(const char* name, int val)
{
	pugi::xml_node text = toeGetConfigNodeText(name);
	char buf [32];
	sprintf(buf,"%d",val);
	text.set_value(buf);
}
void CtoeConfig::SetFloat(const char* name, float val)
{
	pugi::xml_node text = toeGetConfigNodeText(name);
	char buf [32];
	sprintf(buf,"%g",val);
	text.set_value(buf);
}
void CtoeConfig::SetString(const char* name, const char* val)
{
	pugi::xml_node text = toeGetConfigNodeText(name);
	if (!val)
		text.set_value("");
	else
		text.set_value(val);
}
bool CtoeConfig::IsExist(const char* name)
{
	pugi::xml_node text = toeGetConfigNodeText(name);
	const char* v = text.value();
	if (!v || !*v)
		return false;
	return true;
}
int CtoeConfig::GetInteger(const char* name)
{
	pugi::xml_node text = toeGetConfigNodeText(name);
	const char* v = text.value();
	int r = 0;
	if (!v || !*v)
		return r;
	sscanf(v,"%d",&r);
	return r;
}
float CtoeConfig::GetFloat(const char* name)
{
	pugi::xml_node text = toeGetConfigNodeText(name);
	const char* v = text.value();
	float r = 0;
	if (!v || !*v)
		return r;
	sscanf(v,"%f",&r);
	return r;
}
const char* CtoeConfig::GetString(const char* name)
{
	pugi::xml_node text = toeGetConfigNodeText(name);
	const char* v = text.value();
	return v;
}
void CtoeConfig::Load()
{
	if (!toeConfigDocument)
		toeConfigDocument = new pugi::xml_document();

	if (s3eFileCheckExists(toeConfigFilePath))
	{
		pugi::xml_parse_result r = toeConfigDocument->load_file(toeConfigFilePath);
		if (r.status == pugi::status_ok)
			return;
		IwAssertMsg(TOE, false, (r.description()));
	}
	toeConfigDocument->load("<?xml version=\"1.0\" encoding=\"utf-8\" ?><configuration><appSettings></appSettings></configuration>");
}
void CtoeConfig::Save()
{
	if (toeConfigDocument)
		toeConfigDocument->save_file(toeConfigFilePath);
}
void CtoeConfig::Close()
{
	if (toeConfigDocument)
	{
		delete toeConfigDocument;
		toeConfigDocument = 0;
	}
}
