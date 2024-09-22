# 使用官方 Node.js 镜像
FROM node:20

# 设置工作目录
WORKDIR /app

# 复制 package.json 和 package-lock.json
COPY package*.json ./

# 清除之前的 npm 缓存
RUN npm cache clean --force

# 设置新的 npm 镜像地址
RUN npm config set registry https://registry.npmmirror.com

# 安装依赖
RUN npm install

# 复制当前文件夹下的所有文件到工作空间
COPY . .

# 暴露服务端口
EXPOSE 50051

# 启动应用
CMD ["npm", "run", "serve"]

