FROM centos:7
ENV container docker
RUN yum -y install centos-release-scl yum-utils
RUN yum-config-manager --enable rhel-server-rhscl-7-rpms
RUN yum -y install devtoolset-7
RUN yum -y install git tcpdump vim
RUN gcc --version
RUN mkdir /cping
RUN echo PATH="/opt/rh/devtoolset-7/root/usr/bin/:$PATH" >> /etc/bashrc
RUN (cd /lib/systemd/system/sysinit.target.wants/; for i in *; do [ $i == \
systemd-tmpfiles-setup.service ] || rm -f $i; done); \
rm -f /lib/systemd/system/multi-user.target.wants/*;\
rm -f /etc/systemd/system/*.wants/*;\
rm -f /lib/systemd/system/local-fs.target.wants/*; \
rm -f /lib/systemd/system/sockets.target.wants/*udev*; \
rm -f /lib/systemd/system/sockets.target.wants/*initctl*; \
rm -f /lib/systemd/system/basic.target.wants/*;\
rm -f /lib/systemd/system/anaconda.target.wants/*;
VOLUME [ "/sys/fs/cgroup" ]
WORKDIR /cping
CMD ["/usr/sbin/init"]
