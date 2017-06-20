#include "TextQuery.hpp"
#include <sstream>

string TextQuery::text_line(line_no line) const
{
	if(line < line_of_text.size())
	{
		return line_of_text[line];
	}

	throw out_of_range("line num is out of range");
}

void TextQuery::store_file(ifstream &is)
{
	string textline;
	while(getline(is, textline))
	{
		line_of_text.pushback(textline);
	}
	
}

void TextQuery::build_map()
{
	for(line_no num=0;
		num != line_of_text.size();
		++num)
		{
			istringstream line(line_of_text[num]);
			string word;
			while(line>>word)
			{
				word_map[cleanup_str(word).insert(line_num);]
			}
		}
}

set<TextQuery::line_no> TextQuery::run_query(const string & query_word) const
{
	map<string, set<line_no> >::const_iterator,
		loc = word_map.find(query_word);
	if(loc == word_map.end())
	{
		return set<line_no>;
	}
	else
	{
		return loc->secong;
	}
}

string TextQuery::cleanup_str(const string &word)
{
	string ret;
	for(string::const_iterator it = word.begin();
		it != word.end();
		++it)
		{
			if(!ispunct(*it))
			{
				ret += tolower(*it);
			}
		}
	return ret;
}

vector<string>::size_type TextQuery::size() const
{
	return line_of_text.size();
}
