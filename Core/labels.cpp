#include "labels.h"

Labels::Labels()
{
}

Labels::~Labels()
{
}

bool Labels::ReadCSV(const string& filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        return false;
    }
    contents.clear();
    labels.clear();
    this->filepath = "";

    std::string line;
    bool isFirstRow = true;
    std::string currentLine;

    while (std::getline(file, line)) {
        currentLine += line;

        // Check if the line contains open quotes and needs continuation
        int quoteCount = std::count(currentLine.begin(), currentLine.end(), '"');
        if (quoteCount % 2 != 0) {
            // If we have an odd number of quotes, the row is incomplete, continue reading
            currentLine += "\n";
            continue;
        }

        // Parse the complete line now
        std::vector<std::string> row = ParseCSVLine(currentLine);

        if (isFirstRow) {
            isFirstRow = false;  // Skip the first row (attribute names)
            currentLine.clear();
            continue;
        }

        // First column is the string, add it to the vector
        contents.push_back(row[0]);

        // Combine the rest of the columns as 0 or 1
        std::string labelString;
        for (size_t i = 1; i < row.size(); ++i) {
            if (row[i].empty()) {
                labelString += '0';  // Empty cell becomes 0
            }
            else {
                labelString += row[i];  // Non-empty cell becomes 1
            }
        }

        labels.push_back(labelString);
        currentLine.clear();  // Reset for the next row
    }
    file.close();

    if (contents.size() <= 0 || labels.size() <= 0)
        return false;

    this->filepath = filepath;
    return true;
}

void Labels::SaveCSV()
{
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error creating file!" << std::endl;
        return;
    }

    // first row
    file<< "comment_text, Hypertension, Cholesterol, Type 1 diabetes, Type 2 diabetes, Active smoker, Ex - smoker, Family history, Atrial fibrillation, HFpEF, HFrEF, IHD, Non - obstructive coronary atherosclerosis" << std::endl;
    // Write each row to the file
    for (size_t i = 0; i < contents.size(); ++i) {
        // Escape and quote the string if necessary
        std::string escapedString = EscapeAndQuoteCSVField(contents[i]);

        // Write the string (first column) and then each label (separate cells)
        file << escapedString;  // Write the first column (string)

        for (size_t j = 0; j < labels[i].size(); ++j) {
            file << "," << labels[i][j];  // Write each label as a separate cell
        }
        file << std::endl;  // End of row
    }

    file.close();
}

void Labels::SaveCSV(const string& filepath)
{
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error creating file!" << std::endl;
        return;
    }

    // first row
    file << "comment_text, Hypertension, Cholesterol, Type 1 diabetes, Type 2 diabetes, Active smoker, Ex - smoker, Family history, Atrial fibrillation, HFpEF, HFrEF, IHD, Non - obstructive coronary atherosclerosis" << std::endl;
    // Write each row to the file
    for (size_t i = 0; i < contents.size(); ++i) {
        // Escape and quote the string if necessary
        std::string escapedString = EscapeAndQuoteCSVField(contents[i]);

        // Write the string (first column) and then each label (separate cells)
        file << escapedString;  // Write the first column (string)

        for (size_t j = 0; j < labels[i].size(); ++j) {
            file << "," << labels[i][j];  // Write each label as a separate cell
        }
        file << std::endl;  // End of row
    }

    file.close();
    this->filepath = filepath;
}

string Labels::GetContent(int index)
{
    return contents[index];
}

void Labels::SetContent(int index, string newContent)
{
    contents[index] = newContent;
}

string Labels::GetLabels(int index)
{
    return labels[index];
}

void Labels::SetLabels(int index, string newLabel)
{
    labels[index] = newLabel;
}

string Labels::GetLabel(int index, int iLabel)
{
    return labels[index].substr(iLabel,1);
}

void Labels::SetLabel(int index, int iLabel, string newLabel)
{
    labels[index].replace(iLabel, 1, newLabel);
}

int Labels::GetSize()
{
    return contents.size();
}

string Labels::GetFilePath()
{
    return filepath;
}

void Labels::DeleteRecord(int index)
{
    if (contents.size() > 0 && labels.size() > 0)
    {
        contents.erase(contents.begin() + index);
        labels.erase(labels.begin() + index);
    }
}

vector<string> Labels::ParseCSVLine(const string& line)
{
    std::vector<std::string> result;
    std::string cell;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char currentChar = line[i];

        if (currentChar == '"') {
            inQuotes = !inQuotes;  // Toggle the inQuotes flag
        }
        else if (currentChar == ',' && !inQuotes) {
            // If not inside quotes, this comma is a cell delimiter
            result.push_back(cell);
            cell.clear();
        }
        else {
            cell += currentChar;  // Add the character to the current cell
        }
    }

    result.push_back(cell);  // Add the last cell
    return result;
}

string Labels::EscapeAndQuoteCSVField(const string& field)
{
    bool needsQuoting = false;
    std::string result = field;

    // Check if the field contains commas, newlines, or quotes
    if (field.find(',') != std::string::npos || field.find('\n') != std::string::npos || field.find('"') != std::string::npos) {
        needsQuoting = true;
    }

    // Escape quotes by replacing each " with ""
    size_t pos = result.find('"');
    while (pos != std::string::npos) {
        result.insert(pos, "\"");
        pos = result.find('"', pos + 2);  // Move past the escaped quote
    }

    // If quoting is needed, wrap the field in double quotes
    if (needsQuoting) {
        result = "\"" + result + "\"";
    }

    return result;
}
