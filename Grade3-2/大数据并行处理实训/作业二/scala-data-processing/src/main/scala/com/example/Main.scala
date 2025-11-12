package com.example

object Main {
  def main(args: Array[String]): Unit = {
    // 数据去重
    Deduplicate.process(
      List("src/main/resources/deduplicate/file1", "src/main/resources/deduplicate/file2"),
      "output/deduplicate_result.txt"
    )
    
    // 数据排序
    Sort.process(
      List("src/main/resources/sort/file1", "src/main/resources/sort/file2", "src/main/resources/sort/file3"),
      "output/sort_result.txt"
    )
    
    // 平均成绩
    AverageScore.process(
      List("src/main/resources/average/math", "src/main/resources/average/china", "src/main/resources/average/english"),
      "output/average_result.txt"
    )
    
    // 单表关联
    FamilyRelation.process(
      "src/main/resources/relation/family",
      "output/relation_result.txt"
    )
  }
}
