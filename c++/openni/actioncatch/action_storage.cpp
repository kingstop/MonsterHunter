#include "StdAfx.h"
#include "action_storage.h"
#include "../../tinyxml/tinyxml.h"

action_storage::action_storage(void)
{
}


action_storage::~action_storage(void)
{
}


void action_storage::load_from_xml(const char* xml_file)
{
	TiXmlDocument doc(xml_file);
	doc.LoadFile();
	doc.FirstChild()


}
