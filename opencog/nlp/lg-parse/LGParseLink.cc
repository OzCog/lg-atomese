/*
 * LGParseLink.cc
 *
 * Copyright (C) 2017 Linas Vepstas
 *
 * Author: Linas Vepstas <linasvepstas@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the exceptions
 * at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <opencog/atoms/base/Node.h>
#include "LGParseLink.h"

using namespace opencog;

LGParseLink::LGParseLink(const HandleSeq& oset, Type t)
	: FunctionLink(oset, t)
{
	size_t osz = oset.size();
	if (2 != osz)
		throw InvalidParamException(TRACE_INFO,
			"LGParseLink: Expecting two arguments, got %lu", osz);

	Type pht = oset[0]->getType();
	if (PHRASE_NODE != pht and VARIABLE_NODE != pht and GLOB_NODE != pht)
		throw InvalidParamException(TRACE_INFO,
			"LGParseLink: Expecting PhraseNode, got %s",
			oset[0]->toString().c_str());

	Type dit = oset[1]->getType();
	if (LG_DICT_NODE != dit and VARIABLE_NODE != dit and GLOB_NODE != dit)
		throw InvalidParamException(TRACE_INFO,
			"LGParseLink: Expecting LgDictNode, got %s",
			oset[1]->toString().c_str());
}

LGParseLink::LGParseLink(const Link& l)
	: FunctionLink(l)
{
	// Type must be as expected
	Type tparse = l.getType();
	if (not classserver().isA(tparse, LG_PARSE_LINK))
	{
		const std::string& tname = classserver().getTypeName(tparse);
		throw InvalidParamException(TRACE_INFO,
			"Expecting an LgParseLink, got %s", tname.c_str());
	}
}

Handle LGParseLink::execute(AtomSpace* as) const
{
	if (PHRASE_NODE != _outgoing[0]->getType()) return Handle();
	if (LG_DICT_NODE != _outgoing[1]->getType()) return Handle();

	return Handle(createNode(SENTENCE_NODE, "foo"));
}

DEFINE_LINK_FACTORY(LGParseLink, LG_PARSE_LINK)

/* ===================== END OF FILE ===================== */
