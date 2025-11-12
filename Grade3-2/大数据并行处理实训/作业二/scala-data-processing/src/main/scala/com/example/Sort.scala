package com.example

import scala.io.Source
import java.io.PrintWriter

object Sort {
  def process(inputFiles: List[String], outputFile: String): Unit = {
    val numbers = inputFiles
      .flatMap(file => Source.fromFile(file).getLines())
      .filter(_.nonEmpty)
      .map(_.toInt)
      .sorted
    
    val writer = new PrintWriter(outputFile)
    numbers.zipWithIndex.foreach { case (num, idx) =>
      writer.println(s"${idx + 1} $num")
    }
    writer.close()
  }
}
