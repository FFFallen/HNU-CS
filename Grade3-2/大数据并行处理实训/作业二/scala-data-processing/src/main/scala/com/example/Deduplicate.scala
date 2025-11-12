package com.example

import scala.io.Source
import java.io.PrintWriter

object Deduplicate {
  def process(inputFiles: List[String], outputFile: String): Unit = {
    val uniqueLines = inputFiles
      .flatMap(file => Source.fromFile(file).getLines())
      .toSet
    
    val writer = new PrintWriter(outputFile)
    uniqueLines.foreach(writer.println)
    writer.close()
  }
}
