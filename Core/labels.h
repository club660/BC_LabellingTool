#ifndef LABELS_H_
#define LABELS_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class Labels
{
public:
	Labels();
	~Labels();

	bool ReadCSV(const string& filepath);
	void SaveCSV();
	void SaveCSV(const string& filepath);
	string GetContent(int index);
	void SetContent(int index, string newContent);
	string GetLabels(int index);
	void SetLabels(int index, string newLabel);
	string GetLabel(int index, int iLabel);
	void SetLabel(int index, int iLabel, string newLabel);
	int GetSize();
	string GetFilePath();

	void DeleteRecord(int index);

private:
	vector<string> ParseCSVLine(const string& line);
	string EscapeAndQuoteCSVField(const string& field);
private:
	string filepath = "";
	vector<string> contents;
	vector<string> labels;
};

#endif // !LABELS_H_
