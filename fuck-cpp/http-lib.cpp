#include "http-lib.h"
#include <iostream>
#include <sstream>

using namespace std;

vector<string> HTTP::split(string s, string delimiter)
{
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != string::npos)
	{
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

map<string, string> HTTP::mappify1(string const &s, const char delimiter)
{
	map<string, string> m;

	string key, val;
	istringstream iss(s);

	while (getline(getline(iss, key, delimiter) >> ws, val))
		m[key] = val;

	return m;
}

map<string, string> HTTP::vectorToMap(vector<string> vec)
{
	map<string, string> m;

	for (auto elem : vec)
	{

		vector<string> queryEntries = split(elem, "=");

		if (queryEntries.size() < 2)
			continue;

		m[queryEntries.at(0)] = queryEntries.at(1);
	}

	return m;
}

HTTP::HTTP(){

};
string HTTP::httpGet(string name = "")
{
	string queryStr = getenv("QUERY_STRING");

	vector<string> queryEntries = split(queryStr, "&");
	map<string, string> mapEntries = vectorToMap(queryEntries);
	for (auto elem : mapEntries)
	{
		cout << "<p>" << elem.first << " " << elem.second << "</p>";
	}

	if (name == "/cgi-bin/one.cgi")
	{

		if (mapEntries.find("id") == mapEntries.end())
		{
			cout << "<p>Not found</p>";
			return "";
		}
		string id = mapEntries["id"];
		getEntry(id);
	}
	return "";
};
string HTTP::httpPost(string name)
{
	// Post format be like: id=xyz&name=ppp
	string postData;
	cin >> postData;

	vector<string> bodyEntries = split(postData, "&");
	map<string, string> bodyValues = vectorToMap(bodyEntries);

	if (name == "/cgi-bin/post.cgi")
	{
		if (bodyValues.find("id") == bodyValues.end())
		{
			cout << "<p>Provide id</p>";
			return "";
		}
		if (bodyValues.find("name") == bodyValues.end())
		{
			cout << "<p>Provide name</p>";
			return "";
		}
		string id = bodyValues["id"];
		string name = bodyValues["name"];
		return setEntry(id, name);
	}
};
string HTTP::getCookie(string name)
{
	string cookies = getenv("HTTP_COOKIE");
	vector<string> cookiesVector = split(cookies, ";");
	map<string, string> mapEntries = vectorToMap(cookiesVector);
	for (auto elem : mapEntries)
	{
		if (elem.first == name)
		{
			return elem.second;
		}
	}
	return "null";
};
string HTTP::setCookie(string name, string value)
{
	string c = "Set-Cookie: " + name + "=" + value + ";" + "\n";
	cout << c;
	return c;
};
HTTP::~HTTP(){

};

string HTTP::getEntry(string name)
{
	string entry = getCookie(name);
	cout << "<p>" + entry + "</p>";
	return entry;
}

string HTTP::setEntry(string id, string name)
{
	string entryName = "List-" + id;
	string entry = setCookie(entryName, name);
	cout
		<< "Content-Type: text/html; charset=utf-8" << endl
		<< endl;
	cout
		<< "<p>" + name + "</p>\n";
	return entry;
}