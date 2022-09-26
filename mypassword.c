#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <shadow.h>
#include <unistd.h>
#include <pwd.h>
int main(){
	char user[50];
	printf("Username can doi mat khau: ");
	scanf("%s", user);
	struct spwd *spwd = getspnam(user); //truy xuất tên user trong /etc/shadow 
	char *password = getpass("Nhap mat khau cu: "); //nhập lại mật khẩu cũ mà không bị lặp lại 
	char *ecrypted = crypt(password, spwd->sp_pwdp); // Mã hóa mật khẩu cũ sang dạng mật khẩu đã bị mã hóa 
	if(strcmp(ecrypted, spwd->sp_pwdp) != 0){ //So sánh 2 mật khẩu
		printf("Mat khau khong dung!!!\n");
		return 0;
	}
	password = getpass("Nhap mat khau moi: "); //nhập mật khẩu mới 
	ecrypted = crypt(password, spwd->sp_pwdp); //Mã hóa mật khẩu moi
	spwd->sp_pwdp = ecrypted; //cập nhật mật khẩu mới vào /etc/shadow 
	FILE *file = fopen("/etc/shadow", "r"); // mở tệp /etc/shadow với chế độ read
	FILE *fileTemp = fopen("/tmp/replace.tmp", "w"); // mở tệp /tmp/replace.tmp với chế độ write
	if (!file || !fileTemp) {
		printf("Mo file that bai!\n");
		return 0;
	}
	// Đọc từng dòng trong /etc/shadow
	char * line;
	size_t len = 0;
	while (getline(&line, &len, file) != -1) {
		if (strstr(line, user) != NULL) { //nếu dòng này chứa user
			putspent(spwd, fileTemp); // ghi spwd làm định dạng tệp mật khẩu vào /tmp/replace.tmp
		}
		else {
			fputs(line, fileTemp);
		}
	}
	printf("Update thanh cong!!!\n");
	remove("/etc/shadow");	//xóa thư mục /etc/shadow
	rename("/tmp/replace.tmp", "/etc/shadow"); //đổi tên /tmp/replace.tmp sang /etc/shadow

	fclose(file); // đóng file 
	fclose(fileTemp);
	return 0;
	
}

