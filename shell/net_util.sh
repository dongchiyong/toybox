#!/bin/bash

# func：将点分式ip地址转成32位无符号整数
function ip_to_uint32()
{
        ip=$1
        a=`echo $ip | awk -F'.' '{print $1}'`
        b=`echo $ip | awk -F'.' '{print $2}'`
        c=`echo $ip | awk -F'.' '{print $3}'`
        d=`echo $ip | awk -F'.' '{print $4}'`
        echo "$(((a<<24)+(b<<16)+(c<<8)+d))"
}

# func: 判断域名是否可以解析
function if_domain_name_resolved()
    IP_CNT=`dig $1 | grep "$1" | grep -v ";" | wc -l`
    if [ "${IP_CNT}" -lt "1" ];then
        echo 0
    else
		echo 1
	fi
}

# func：判断ip地址是否为内网ip
function is_inner_ip()
{
	ipval=\`ip2num $1\`
    # check if the ip between "10.0.0.0" and "10.255.255.255" or between "172.16.0.0" or between "172.31.255.255"
    if ([ $ipval -gt 167772160 ] && [ $ipval -lt 184549375 ]) || ([ $ipval -gt 2886729728 ] && [ $ipval -lt 2887778303 ]);then
        echo 1
	else
		echo 0
	fi
}

# 下载文件
function download()
{
	wget $1
}
