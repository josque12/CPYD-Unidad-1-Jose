FROM fedora:42

RUN dnf update -y
RUN dnf install -y ninja gcc vim gcc gcc-c++ clang openssh-server lldb clangd libicu python3 pip cmake perl gdb awk npm git bison flex autoconf

RUN git clone --depth 1 https://github.com/microsoft/vcpkg.git /opt/vcpkg/
RUN /opt/vcpkg/bootstrap-vcpkg.sh
RUN echo 'export PATH=/opt/vcpkg/:$PATH' >> ~/.bashrc
RUN sed -i 's/#Port 22/Port 22/g' /etc/ssh/sshd_config
RUN sed -i 's/#PermitRootLogin.*/PermitRootLogin yes/g' /etc/ssh/sshd_config

RUN ssh-keygen -A
RUN touch ~/.ssh/authorized_keys && chmod 600 ~/.ssh/authorized_keys

RUN mkdir /devenv && mkdir /devenv/workspace && mkdir /devenv/workspace/service

#copy public key into container for autmatic login
COPY id_ed25519.pub /devenv

RUN cat /devenv/id_ed25519.pub > ~/.ssh/authorized_keys

EXPOSE 22 8080

CMD ["/usr/sbin/sshd", "-D"]
