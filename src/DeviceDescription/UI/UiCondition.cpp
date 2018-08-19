/* Copyright 2013-2017 Sathya Laufer
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

#include "UiCondition.h"
#include "../../BaseLib.h"

namespace BaseLib
{
namespace DeviceDescription
{

UiCondition::UiCondition(BaseLib::SharedObjects* baseLib)
{
    _bl = baseLib;
}

UiCondition::UiCondition(BaseLib::SharedObjects* baseLib, xml_node<>* node) : UiCondition(baseLib)
{
    for(xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute())
    {
        std::string name(attr->name());
        std::string value(attr->value());
        if(name == "operator") conditionOperator = value;
        else if(name == "value") conditionValue = value;
        else _bl->out.printWarning("Warning: Unknown attribute for \"condition\": " + std::string(attr->name()));
    }
    for(xml_node<>* subNode = node->first_node(); subNode; subNode = subNode->next_sibling())
    {
        std::string name(subNode->name());
        std::string value(subNode->value());
        if(name == "icons")
        {
            for(xml_node<>* iconNode = subNode->first_node("icon"); iconNode; iconNode = iconNode->next_sibling("icon"))
            {
                icons.emplace_back(std::make_shared<UiIcon>(baseLib, iconNode));
            }
        }
        else if(name == "texts")
        {
            for(xml_node<>* textNode = subNode->first_node("text"); textNode; textNode = textNode->next_sibling("text"))
            {
                auto text = std::make_shared<UiText>(baseLib, textNode);
                if(!text->id.empty()) texts.emplace(text->id, std::move(text));
            }
        }
        else _bl->out.printWarning("Warning: Unknown node in \"condition\": " + name);
    }
}

UiCondition::UiCondition(UiCondition const& rhs)
{
    _bl = rhs._bl;

    conditionOperator = rhs.conditionOperator;
    conditionValue = rhs.conditionValue;

    for(auto& icon : rhs.icons)
    {
        auto uiIcon = std::make_shared<UiIcon>(_bl);
        *uiIcon = *icon;
        icons.emplace_back(uiIcon);
    }

    for(auto& text : rhs.texts)
    {
        auto uiText = std::make_shared<UiText>(_bl);
        *uiText = *(text.second);
        texts.emplace(uiText->id, std::move(uiText));
    }
}

UiCondition& UiCondition::operator=(const UiCondition& rhs)
{
    if(&rhs == this) return *this;

    _bl = rhs._bl;

    conditionOperator = rhs.conditionOperator;
    conditionValue = rhs.conditionValue;

    for(auto& icon : rhs.icons)
    {
        auto uiIcon = std::make_shared<UiIcon>(_bl);
        *uiIcon = *icon;
        icons.emplace_back(uiIcon);
    }

    for(auto& text : rhs.texts)
    {
        auto uiText = std::make_shared<UiText>(_bl);
        *uiText = *(text.second);
        texts.emplace(uiText->id, std::move(uiText));
    }

    return *this;
}

}
}