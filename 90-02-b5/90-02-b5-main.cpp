/*2151613 毛宇录 计科*/
#include "90-02-b5.h"

const char* path = "./book/";
const char* to_search = "./book/*.txt";
#define max_size (20*1024*1024)

int main()
{
	while (1) {
		string file_name;
		list_board(file_name, path, to_search, 4);
		Sleep(500);
		cct_cls();
		bool flag_quit = false;
		//开始读入文件
		file_name = path + file_name;
		ifstream fin;
		fin.open(file_name, ios::in);
		if (fin.fail()) {
			cout << "文件打开失败!!!" << endl;
			Sleep(1000);
			continue;
		}
		int size = file_size(fin);
		if (size > max_size) {
			cout << "文件太大，无法打开!!!" << endl;
			Sleep(1000);
			continue;
		}
		while (1) {
			//show_page();
			string temp;
			getline(fin, temp);
			cout << temp;
			int MX = 0, MY = 0, MAction = 0, keycode1 = 0, keycode2 = 0;
			cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
			if (keycode1 == 224) {
				if (keycode2 == 72) {//上箭头

				}
				else if (keycode2 == 80) {//下箭头

				}
				else if (keycode2 == 73) {//PgUp

				}
				else if (keycode2 == 81) {//PgDn

				}
			}
			else if (keycode1 == 'q' || keycode1 == 'Q') {
				flag_quit = true;
				break;
			}
			else if (keycode1 == 's' || keycode1 == 'S') {

			}
			else if (keycode1 == 'n' || keycode1 == 'N')
				break;
			else if (keycode1 == 'f' || keycode1 == 'F') {

			}
		}
		fin.close();
		if (flag_quit == true)
			break;
	}
	return 0;
}