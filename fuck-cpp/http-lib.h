#include <string>
#include <vector>
#include <map>

using namespace std;

class HTTP
{
public:
	HTTP();
	string httpGet(string name);
	string httpPost(string name);
	string getCookie(string name);
	string setCookie(string name, string value);
	~HTTP();

private:
	vector<string> split(string s, string delimiter);

	map<string, string> mappify1(string const &s, const char delimiter);

	map<string, string> vectorToMap(vector<string> vec);

	string setEntry(string id, string value);

	string getEntry(string id);
};
