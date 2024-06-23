#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <clocale>
#include <cwchar>

class Table {
private:
    std::vector<std::vector<std::string>> rows;
    std::vector<int> col_widths;
    std::vector<std::string> formattedRows;

    // 计算字符串的显示宽度，考虑中文字符
    int string_display_width(const std::string &str) const {
        std::setlocale(LC_ALL, "");
        const char *c_str = str.c_str();
        size_t bytes = str.size();
        mbstate_t state{};
        int width = 0;

        while (bytes > 0) {
            wchar_t wc;
            size_t len = mbrtowc(&wc, c_str, bytes, &state);
            if (len == (size_t) (-1) || len == (size_t) (-2)) {
                break; // 编码错误
            }
            c_str += len;
            bytes -= len;
            width += wcwidth(wc);
        }

        return width;
    }

    // 更新格式化行
    void updateFormattedRows() {
        formattedRows.clear();
        std::string border = "+";
        for (int width: col_widths) {
            border += std::string(width + 2, '-') + "+";
        }

        formattedRows.push_back(border);

        for (const auto &row: rows) {
            std::stringstream ss;
            ss << "|";
            for (size_t i = 0; i < row.size(); ++i) {
                ss << " " << row[i];
                int padding = col_widths[i] - string_display_width(row[i]);
                ss << std::string(padding, ' ') << " |";
            }
            formattedRows.push_back(ss.str());
            formattedRows.push_back(border); // 添加每行下方的边框
        }
    }

public:
    Table() {}

    void add_row(const std::vector<std::string> &row) {
        rows.push_back(row);
        if (col_widths.size() < row.size()) {
            col_widths.resize(row.size(), 0);
        }
        for (size_t i = 0; i < row.size(); ++i) {
            col_widths[i] = std::max(col_widths[i], string_display_width(row[i]));
        }
        updateFormattedRows();
    }

    const std::vector<std::string> &getFormattedRows() const {
        return formattedRows;
    }

    static std::vector<wchar_t> get_characters(const std::string& str) {
        std::setlocale(LC_ALL, ""); // 设置环境为默认的本地环境，支持UTF-8
        std::vector<wchar_t> characters;

        const char* c_str = str.c_str(); // 获取C风格的字符串
        size_t bytes = str.size(); // 获取字节大小
        mbstate_t state = mbstate_t(); // 初始化转换状态

        while (bytes > 0) {
            wchar_t wc; // 宽字符
            size_t length = mbrtowc(&wc, c_str, bytes, &state); // 将多字节字符转换为宽字符

            if (length == (size_t)-1 || length == (size_t)-2) {
                break; // 如果转换失败，则停止
            }

            characters.push_back(wc); // 将字符添加到向量
            c_str += length; // 移动指针
            bytes -= length; // 减少剩余字节数
        }

        return characters;
    }

    static int wchar_display_width(wchar_t wc) {
        // CJK 字符范围，假设是全角
        if ((wc >= 0x1100 && wc <= 0x11FF) ||   // 谚文字母
            (wc >= 0x2E80 && wc <= 0x9FFF) ||   // CJK 统一表意符号
            (wc >= 0xAC00 && wc <= 0xD7AF) ||   // 谚文音节
            (wc >= 0x3000 && wc <= 0x303F) ||   // CJK 符号和标点
            (wc >= 0xFF00 && wc <= 0xFF60) ||   // 全角ASCII
            (wc >= 0xFFE0 && wc <= 0xFFE6)      // 全角符号
                ) {
            return 2; // 全角字符
        }
        return 1; // 半角字符
    }

};


/*
 *
    // DEMO:
    Table table;
    table.add_row({"Name", "Age", "Occupation"});
    table.add_row({"Alice", "24", "Software Engineer"});
    table.add_row({"Bob", "19", "Student"});
    table.add_row({"Charlie", "29", "Doctor"});

    const auto& rows = table.getFormattedRows();
    for (const auto& row : rows) {
        std::cout << row << std::endl;
    }

 */