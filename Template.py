import os

newpage = "<div style=\"page-break-after: always;\"></div>"

def generate_markdown():
    # 创建并打开 Template.md 文件
    with open("README.md", "w", encoding="utf-8") as md_file:
        # 写入一级标题
        md_file.write("# Template\n\n")
        
        # 初始化目录内容
        toc = "## 目录\n\n"
        content = ""
        
        # 遍历当前目录下的所有文件夹
        for root, dirs, files in os.walk("."):
            for dir_name in dirs:
                dir_path = os.path.join(root, dir_name)
                cpp_files = [f for f in os.listdir(dir_path) if f.endswith(".cpp")]
                
                if cpp_files:
                    # 写入目录中的二级标题
                    toc += f"- [{dir_name}](#{dir_name.replace(' ', '-').lower()})\n"
                    
                    # 写入二级标题
                    content += f"\n\n## {dir_name}\n\n"
                    
                    # 遍历文件夹中的所有 .cpp 文件
                    for cpp_file in cpp_files:
                        file_path = os.path.join(dir_path, cpp_file)
                        
                        # 写入目录中的三级标题
                        toc += f"  - [{cpp_file}](#{cpp_file.replace(' ', '-').replace('.', '').lower()})\n"
                        
                        # 写入三级标题
                        content += f"### {cpp_file}\n\n"
                        
                        # 读取 .cpp 文件内容并写入到 Markdown 文件中
                        with open(file_path, "r", encoding="utf-8") as cpp_file_content:
                            content += "```cpp\n"
                            content += cpp_file_content.read()
                            content += "\n```\n"
                    
                    # 添加分页符
                    content += "\n" + newpage + "\n"
        
        # 将目录和内容写入到文件中
        md_file.write(toc + "\n\n" + content)

if __name__ == "__main__":
    generate_markdown()
