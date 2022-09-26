#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
int main(){
	char s[50];
	printf("Nhap Username: ");
	scanf("%s", s);
	struct passwd *p = getpwnam(s);
	if(p == NULL){
		printf("Khong tim thay user!\n");
		return 0;
	}
	int ngroups = 0;
	getgrouplist(p->pw_name, p->pw_gid, NULL, &ngroups);
	gid_t groups[ngroups];
	// here we actually get the groups
	getgrouplist(p->pw_name, p->pw_gid, groups, &ngroups);
	printf("Thong tin id: %d\n", p->pw_uid);
	printf("Username: %s\n", p->pw_name);
	printf("Thu muc home: %s\n", p->pw_dir);
	printf("Danh sach groups: ");
	for(int i=0; i<ngroups; i++){
		printf("%s ", getgrgid(groups[i])->gr_name);
	}
	printf("\n");
}
