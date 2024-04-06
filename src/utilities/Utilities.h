#pragma once

#define EXCEL_PATH R"("C:\Program Files\Microsoft Office\root\Office16\EXCEL.EXE")"  // R"("C:\Program Files (x86)\Microsoft Office\Office14\EXCEL.EXE")"
// TODO: R"("C:\Program Files\Microsoft Office\root\Office16\EXCEL.EXE")"
#define CHROME_PATH R"("C:\Program Files\Google\Chrome\Application\chrome.exe")"  // R"("C:\Program Files (x86)\Google\Chrome\Application\chrome.exe")"
// TODO: R"("C:\Program Files\Google\Chrome\Application\chrome.exe")"

bool is_csv_file(const char* file_name);

bool is_html_file(const char* file_name);

void launch_file_in_excel(const char* file_name);

void launch_file_in_html(const char* file_name);
