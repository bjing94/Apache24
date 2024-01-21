#include <iostream>
#include <functional>
#include <map>
#include <sstream>
#include "http-lib.h"

using namespace std;

int main()
{
	HTTP http = HTTP();

	cout
		<< "Content-Type: text/html; charset=utf-8" << endl
		<< endl;

	string scriptName = getenv("SCRIPT_NAME");
	http.httpGet(scriptName);
	return -1;
}
