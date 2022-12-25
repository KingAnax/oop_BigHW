/*2151613 ë��¼ �ƿ�*/
#include "90-02-b5.h"

const char* path = "./book/";
const char* to_search = "./book/*.txt";
const char* sav_name = "./book/position.sav";
#define max_size (20*1024*1024)

int main()
{
	while (1) {
		string file_name;
		list_board(file_name, path, to_search, 4);
		Sleep(500);

		bool flag_quit = false;
		struct page mypage;
		mypage.show_format = 1;

		/*�����ȶ�ȡ�����ļ�*/
		mypage.start_pos = read_sav(sav_name, file_name);

		//��ʼ�����ļ�
		ifstream fin;
		fin.open(path + file_name, ios::in);
		if (fin.fail()) {
			cout << "�ļ���ʧ��!!!" << endl;
			Sleep(1000);
			continue;
		}

		int size = file_size(fin);
		if (size > max_size) {
			cout << "�ļ�̫���޷���!!!" << endl;
			Sleep(1000);
			continue;
		}

		if (mypage.start_pos > size || mypage.start_pos < 0)
			mypage.start_pos = 0;

		fin.seekg(mypage.start_pos, ios::beg);
		read_page_down(mypage, fin);

		//�����
		draw_frame();
		addition_line();
		//��ʾ�Ķ����沢���в���
		while (1) {
			show_page(mypage, fin);
			info_line(mypage.end_pos, file_name, size);
			int MX = 0, MY = 0, MAction = 0, keycode1 = 0, keycode2 = 0;
			bool flag_read = false;
			while (1) {
				my_read_keyboard(keycode1, keycode2);
				if (keycode1 == 224) {
					if (keycode2 == KB_ARROW_UP) {//�ϼ�ͷ
						break;
					}
					else if (keycode2 == KB_ARROW_DOWN) {//�¼�ͷ
						if (fin.eof())
							continue;
						roll_down_single(mypage, fin);
						mypage.start_pos = mypage.myline[0].line_first_pos;
						break;
					}
					else if (keycode2 == KB_PAGE_UP) {//pgup
						break;
					}
					else if (keycode2 == KB_PAGE_DOWN) {//pgdn
						if (fin.eof())
							continue;
						roll_down_page(mypage, fin);
						mypage.start_pos = mypage.myline[0].line_first_pos;
						break;
					}
				}
				else if (keycode1 == 'q' || keycode1 == 'Q') {
					flag_read = true;
					flag_quit = true;
					break;
				}
				else if (keycode1 == 's' || keycode1 == 'S') {
					goto_line(mypage, fin, size);
					break;
				}
				else if (keycode1 == 'n' || keycode1 == 'N') {
					flag_read = true;
					break;
				}
				else if (keycode1 == 'f' || keycode1 == 'F') {
					change_format(mypage, fin);
					break;
				}
			}
			if (flag_read)
				break;
		}
		fin.close();
		/*������Ϣ*/
		write_sav(mypage.start_pos, sav_name, file_name);

		if (flag_quit == true)
			break;
	}
	return 0;
}