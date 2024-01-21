#include <iostream>
#include <functional>
#include <map>
#include <sstream>
#include "http-lib.h"

using namespace std;

int main()
{
	HTTP http = HTTP();

	string scriptName = getenv("SCRIPT_NAME");
	http.httpPost(scriptName);
	return -1;
}
