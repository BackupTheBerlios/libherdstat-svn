distapp = herdstat-test-data
distver := $(shell date --iso | sed -e 's~-~~g')
distpkg := $(distapp)-$(distver)

dirs = localstatedir portdir

dist:
	mkdir "$(distpkg)"
	cp -R $(dirs) "$(distpkg)"
	find "$(distpkg)" -type d -name '.svn' -exec rm -fr {} \; 2>/dev/null || true
	tar jcf "$(distpkg).tar.bz2" "$(distpkg)"
	rm -fr "$(distpkg)/"

dist-sign: dist
	gpg --armour --detach-sign "$(distpkg).tar.bz2"

dist-upload: dist dist-sign
	echo -ne "user anonymous libherdstat\ncd incoming\nput $(distpkg).tar.bz2\nput $(distpkg).tar.bz2.asc\nbye" | \
                ftp -n ftp.berlios.de

