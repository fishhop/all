#include "TextQuery.hpp"
#include "Query.hpp"

string make_plural(size_t, const string, const string &);
ifstream & open_file(ifstream &, const string &);
void print_results(const set<TextQuery::line_no> &locs, const TextQuery & file)
{
	typedef set<TextQuery::line_no> line_num;
	line_num::size_type size = locs.size();
	cout << "match occurs " << size << " " 
		<< make_plural(size, "time", "s") <<endl;
	line_num::const_iterator it = locs.begin();
	for(; it != locs.end(); ++it)
	{
		cout << "\t<line "
			 << *it + 1 << ") "
			 << file.text_line(*it) << endl;
	}
}

int main(int argc, char **argv)
{
	ifstream infile;
	if(argc < 2 || !open_file(infile, argv[1]))
	{
		cerr << "No input file!" << endl;
		return EXIT_FAILURE;
	}

	TextQuery file;
	file.read_file(infile);
	typeded set<TextQuery::line_no> line_no
	Query q = Query("fiery") & Query("bird") | Query("wind");

	const line_no &locs = q.eval(file);

	cout << "\nExecuted Query for: " << q << endl;

	print_results(locs, file);

	return 0;

}
