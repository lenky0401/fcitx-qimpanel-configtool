fcitx-qimpanel-configtool
=========================
Create debian package
1.make clean，并移出debian文件夹和
2.将文件夹改名为fcitx-qimpanel-configtool-0.1
3.压缩文件夹
4.进入文件夹执行dh_make -f ../fcitx-qimpanel-configtool.tar.gz
5.删除生成的debian文件夹
6.将移除的debian文件夹拷贝进来
7.进入文件夹执行dpkg-buildpackage -rfakeroot [-nc]
	-nc 代表 no clean
==========================
安装是如果提示硬链接已存在，请删除对应硬链接
==========================
A qt4.8 based configurae tool for fcitx-qimpanel.

This is a qt-creator project.
