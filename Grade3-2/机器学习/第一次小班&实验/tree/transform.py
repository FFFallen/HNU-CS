import pandas as pd

# =======================
# 1. 原封不动读取 txt 并保存为 csv
# =======================
# 假设输入文件为逗号分隔的 txt（字段顺序与标签顺序一致）
df = pd.read_csv(
    "car_1000.txt",  # 替换为你的 txt 文件路径
    delimiter=",",  # 根据实际分隔符调整（如空格用 " "）
    header=None,    # 如果 txt 无列名
    names=['buying', 'maint', 'doors', 'persons', 'lug_boot', 'safety']  # 强制指定标签
)

# 直接保存为 CSV（不修改任何数据）
df.to_csv(
    "car_1000.csv",  # 输出文件名
    index=False,    # 不保存行索引
    header=True     # 保留列名
)

print("转换完成！生成的 CSV 文件包含以下列：")
print(df.columns.tolist())