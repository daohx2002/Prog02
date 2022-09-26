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
	FILE *file = fopen("/etc/shadow", "r");
	FILE *fileTemp = fopen("/tmp/replace.tmp", "w");
	if (!file) {
		printf("Mo file that bai!\n");
		exit(EXIT_FAILURE);
	}
	// Đọc từng dòng trong /etc/shadow
	char * line;
	size_t len = 0;
	while (getline(&line, &len, file) != -1) {
		if (strstr(line, user) != NULL) { //nếu dòng này chứa user
			putspent(spwd, fileTemp);
			//putspent(spwd, file);
		}
		else {
			fputs(line, fileTemp);
		}
	}
	printf("Update thanh cong!!!\n");
	remove("/etc/shadow");
	rename("/tmp/replace.tmp", "/etc/shadow");

	fclose(file);
	fclose(fileTemp);
	exit(EXIT_SUCCESS);
	
}

