#include "Query.hpp"
#include "TextQuery.hpp"
#include <set>
#include <iostream>

using namespace std;

set <line_no> NotQuery::eval(const TextQuery & file) const
{
	
	set <line_no> ret_lines;
	set <line_no> has_val = query.eval(file);
	for(line_no n = 0; n != file.size(); ++n)
	{
		if(has_val.find(n) == has_val.end())
		{
			ret_lines.insert(n);
		}
	}

	return ret_lines;
}

set <line_no> AndQuery::eval(const TextQuery & file) const
{
	set <line_no> left = lhs.eval(file),
					right = rhs.eval(file);
	set <line_no> ret_lines;

	set_intersection(left.begin(), left.end(),
					right.begin(), right.end(),
					inserter(ret_lines, ret_lines.begin()));
	
	retrun ret_lines;
}

set <line_no> OrQuery::eval(const TextQuery & file) const
{
	set <line_no> left = lhs.eval(file),
					right = rhs.eval(file);

	for(set<line_no>::const_iterator it = right.begin();
		it != it.end(); ++it)
	{
		ret_lines.insert(*it);
	}

	return ret_lines;
}

