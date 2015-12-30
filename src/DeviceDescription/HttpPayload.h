/* Copyright 2013-2015 Sathya Laufer
 *
 * libhomegear-base is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * libhomegear-base is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with libhomegear-base.  If not, see
 * <http://www.gnu.org/licenses/>.
 * 
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU Lesser General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
*/

#ifndef HTTPPAYLOAD_H_
#define HTTPPAYLOAD_H_

#include "../Encoding/RapidXml/rapidxml.hpp"
#include <string>
#include <vector>
#include <memory>

using namespace rapidxml;

namespace BaseLib
{

class Obj;

namespace DeviceDescription
{

class HttpPayload;

typedef std::shared_ptr<HttpPayload> PHttpPayload;
typedef std::vector<PHttpPayload> HttpPayloads;

class HttpPayload
{
public:
	HttpPayload(BaseLib::Obj* baseLib);
	HttpPayload(BaseLib::Obj* baseLib, xml_node<>* node);
	virtual ~HttpPayload() {}

	std::string key;
	std::string parameterId;
	bool constValueBooleanSet = false;
	bool constValueBoolean = false;
	bool constValueIntegerSet = false;
	int32_t constValueInteger = -1;
	bool constValueDecimalSet = false;
	double constValueDecimal = -1;
	bool constValueStringSet = false;
	std::string constValueString;
protected:
	BaseLib::Obj* _bl = nullptr;
};
}
}

#endif
