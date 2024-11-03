#include <iostream>
#include <list>
#include <forward_list>
#include <vector>
#include <algorithm>
#include <string>
#include <regex>

using namespace std;

struct Book {
	string title;//書名
	string author;//作者
	string id;//圖書編號
};

struct Borrower {//借閱者
	string name;//姓名
	vector<string> borrowedBooks;//借閱的圖書編號
};

list<Book> books;//圖書
forward_list<Borrower> borrowers;//借閱者

bool isValidBookId(const string& id) {//判斷圖書編號是否有效
	regex pattern("^[A-Z][0-9]{4}$");//正則表達式
	return regex_match(id, pattern);//匹配
}

void addBook() {//添加圖書
	Book book;//書
	cout << "輸入書名: ";//輸入書名
	cin >> book.title;//輸入書名
    cout << "輸入作者: ";
    cin >> book.author;
    do {
        cout << "輸入圖書編號 (格式: A1234): ";
		cin >> book.id;//輸入圖書編號
		if (!isValidBookId(book.id)) {//判斷圖書編號是否有效
            cout << "圖書編號格式錯誤，請重新輸入。\n";
        }
	} while (!isValidBookId(book.id));//判斷圖書編號是否有效
	books.push_back(book);//添加圖書
    cout << "圖書已添加。\n";
}

void deleteBook() {//刪除圖書
	string id;//圖書編號
    cout << "輸入要刪除的圖書編號: ";
    cin >> id;
	books.remove_if([&id](const Book& book) { return book.id == id; });//刪除圖書
    cout << "圖書已刪除。\n";
}

void searchBook() {//搜索圖書
    string id;
    cout << "輸入要搜索的圖書編號: ";
    cin >> id;
	for (const auto& book : books) {//遍歷圖書
		if (book.id == id) {//搜索圖書
            cout << "書名: " << book.title << ", 作者: " << book.author << ", 圖書編號: " << book.id << endl;
            return;
        }
    }
    cout << "未找到圖書。\n";
}

void listBooks() {
	books.sort([](const Book& a, const Book& b) { return a.id < b.id; });//排序
	for (const auto& book : books) {//遍歷圖書
		cout << "書名: " << book.title << ", 作者: " << book.author << ", 圖書編號: " << book.id << endl;// 輸出書名、作者、圖書編號
    }
}

void addBorrower() {//添加借閱者
	Borrower borrower;//借閱者
	cout << "輸入借閱者姓名: ";//輸入借閱者姓名
	cin >> borrower.name;//輸入借閱者姓名
	int numBooks;//借閱的圖書數量
	cout << "輸入借閱的圖書數量: ";//輸入借閱的圖書數量
	cin >> numBooks;//輸入借閱的圖書數量
	for (int i = 0; i < numBooks; ++i) {//遍歷借閱的圖書
		string bookId;//圖書編號
        cout << "輸入借閱的圖書編號: ";
        cin >> bookId;
		borrower.borrowedBooks.push_back(bookId);//添加借閱的圖書
    }
	borrowers.push_front(borrower);//添加借閱者
    cout << "借閱者已添加。\n";
}

void deleteBorrower() {//刪除借閱者
	string name;//借閱者姓名
    cout << "輸入要刪除的借閱者姓名: ";
    cin >> name;
	borrowers.remove_if([&name](const Borrower& borrower) { return borrower.name == name; });//刪除借閱者
    cout << "借閱者已刪除。\n";
}

void searchBorrower() {//搜索借閱者
	string name;//借閱者姓名
    cout << "輸入要搜索的借閱者姓名: ";
    cin >> name;
	for (const auto& borrower : borrowers) {//遍歷借閱者
		if (borrower.name == name) {//搜索借閱者
            cout << "姓名: " << borrower.name << ", 借閱的圖書編號: ";
			for (const auto& bookId : borrower.borrowedBooks) {//遍歷借閱的圖書
                cout << bookId << " ";
            }
            cout << endl;
            return;
        }
    }
    cout << "未找到借閱者。\n";
}

void listBorrowers() {//列出所有借閱者
	for (const auto& borrower : borrowers) {//遍歷借閱者
        cout << "姓名: " << borrower.name << ", 借閱的圖書編號: ";
		for (const auto& bookId : borrower.borrowedBooks) {//遍歷借閱的圖書
            cout << bookId << " ";
        }
        cout << endl;
    }
}

int main() {
	int choice;//選擇
    do {
        cout << "1. 添加新圖書\n";
        cout << "2. 刪除圖書\n";
        cout << "3. 搜索圖書\n";
        cout << "4. 列出所有圖書\n";
        cout << "5. 添加新借閱者\n";
        cout << "6. 刪除借閱者\n";
        cout << "7. 搜索借閱者\n";
        cout << "8. 列出所有借閱者\n";
        cout << "0. 退出\n";
        cout << "選擇操作: ";
        cin >> choice;
        switch (choice) {
		case 1: addBook(); break;//添加圖書
		case 2: deleteBook(); break;//刪除圖書
		case 3: searchBook(); break;//搜索圖書
		case 4: listBooks(); break;//列出所有圖書
		case 5: addBorrower(); break;//添加借閱者
		case 6: deleteBorrower(); break;//刪除借閱者
		case 7: searchBorrower(); break;//搜索借閱者
		case 8: listBorrowers(); break;//列出所有借閱者
		case 0: break;//退出
		default: cout << "無效的選擇。\n"; break;//無效的選擇
        }
    } while (choice != 0);
    return 0;
}