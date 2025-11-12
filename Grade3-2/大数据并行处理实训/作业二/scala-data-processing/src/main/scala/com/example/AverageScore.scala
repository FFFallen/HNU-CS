package com.example

import scala.io.Source
import java.io.PrintWriter
import scala.collection.mutable

object AverageScore {
  def process(inputFiles: List[String], outputFile: String): Unit = {
    val studentScores = mutable.Map[String, List[Int]]()
    
    inputFiles.foreach { file =>
      Source.fromFile(file).getLines().foreach { line =>
        val parts = line.split("\\s+")
        if (parts.length == 2) {
          val name = parts(0)
          val score = parts(1).toInt
          studentScores(name) = studentScores.getOrElse(name, Nil) :+ score
        }
      }
    }
    
    val writer = new PrintWriter(outputFile)
    studentScores.foreach { case (name, scores) =>
      val avg = scores.sum.toDouble / scores.length
      writer.println(s"$name ${avg.round}")
    }
    writer.close()
  }
}
