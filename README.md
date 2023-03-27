rssSearchEngine
-----

### 前端搭建

1. 安装apache2
``` bash
sudo apt-get install -y apache2
```

2. 安装php libapache2-mod-php
``` bash
sudo apt-get install -y php libapache2-mod-php
```

3. 将SearchEngine文件夹复制到 /var/www/html/ 目录下
``` bash
sudo cp -r SearchEngine /var/www/html/
```

### 服务器搭建

#### 安装所依赖的三方库
``` bash
./build.sh
```
