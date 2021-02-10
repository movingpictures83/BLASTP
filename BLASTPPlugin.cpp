#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "BLASTPPlugin.h"


void BLASTPPlugin::input(std::string file) {
 inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 while (!ifile.eof()) {
   std::string key, value;
   ifile >> key;
   ifile >> value;
   parameters[key] = value;
 }

}

void BLASTPPlugin::run() {}

void BLASTPPlugin::output(std::string file) {
 std::string outputfile = file;
 std::string myCommand = "";

 //blastp -query "+organism1+".faa -db "+organism2+".db -outfmt 6 > "+organism1+"_"+organism2+".txt"
 //makeblastdb -in PA14.txt -out PA14.db
myCommand += "blastp";
myCommand += " ";
myCommand += "-query";
myCommand += " ";
myCommand += std::string(PluginManager::prefix()) + "/" + parameters["query"] + " ";
myCommand += "-db";
myCommand += " ";
myCommand += std::string(PluginManager::prefix()) + "/" + parameters["db"] + " ";
myCommand += "-outfmt";
myCommand += " ";
myCommand += parameters["outfmt"] + " ";
myCommand += ">";
myCommand += " ";
myCommand += outputfile;
 system(myCommand.c_str());
}

PluginProxy<BLASTPPlugin> BLASTPPluginProxy = PluginProxy<BLASTPPlugin>("BLASTP", PluginManager::getInstance());
