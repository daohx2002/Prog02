#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
int main(){
	char s[50];
	printf("Nhap Username: ");
	scanf("%s", s);
	struct passwd *p = getpwnam(s); //tìm dòng trong /etc/passwd có chưa tên người dùng là s
	if(p == NULL){
		printf("Khong tim thay user!\n");
		return 0;
	}
	// lấy danh sách các nhóm (GID) mà nguời dùng *p thuộc về 
	int ngroups = 0; //số lượng nhóm = 0 
	getgrouplist(p->pw_name, p->pw_gid, NULL, &ngroups); //lấy đúng các ngroups 
	gid_t groups[ngroups];
	getgrouplist(p->pw_name, p->pw_gid, groups, &ngroups); //các nhóm nhận đc 
	printf("Thong tin id: %d\n", p->pw_uid);
	printf("Username: %s\n", p->pw_name);
	printf("Thu muc home: %s\n", p->pw_dir);
	printf("Danh sach groups: ");
	for(int i=0; i<ngroups; i++){
		printf("%s ", getgrgid(groups[i])->gr_name); //trả về các nhóm mà user thuộc về 
	}
	printf("\n");
}
