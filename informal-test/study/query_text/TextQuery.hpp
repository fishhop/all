#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H

#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

class TextQuery
{
	public:
		typedef string::size_type str_size;
		typedef vecotr<string>::size_type line_no;

		void read_file(ifstream &is)
		{
			store_file(is);
			build_map();
		}
		set<line_no> run_query(const string &) const;

		string text_line(line_no) const;
		line_no size() const;
	private:
		void store_file(ifstream &);
		void build_map();
		vector<string> line_of_text;
		map<string, set<line_no> >word_map;
		static string cleanup_str(const string &);
		
};
	
#endif
