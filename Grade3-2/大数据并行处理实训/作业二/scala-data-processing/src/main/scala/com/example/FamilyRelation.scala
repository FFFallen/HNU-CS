package com.example

import scala.io.Source
import java.io.PrintWriter

object FamilyRelation {
  case class Relation(child: String, parent: String)
  
  def process(inputFile: String, outputFile: String): Unit = {
    val relations = Source.fromFile(inputFile).getLines()
      .filter(_.nonEmpty)
      .map { line =>
        val parts = line.split("\\s+")
        Relation(parts(0), parts(1))
      }.toList
    
    val grandRelations = for {
      r1 <- relations
      r2 <- relations if r1.parent == r2.child
    } yield s"${r1.child} ${r2.parent}"
    
    val writer = new PrintWriter(outputFile)
    grandRelations.distinct.foreach(writer.println)
    writer.close()
  }
}
