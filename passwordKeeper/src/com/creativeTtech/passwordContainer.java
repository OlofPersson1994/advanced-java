package com.creativeTtech;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class passwordContainer {

    File passwordFile = new File("passwords2.txt");
    FileWriter fileWriter = new FileWriter("passwords2.txt");

    public LinkedList<String> list = new LinkedList<>();

    public passwordContainer() throws IOException {

        //createNewFile();
    }

    void printList(LinkedList list){

        if(list.size() == 0){
            System.out.printf("The list with password is empty.\n\n");
            return;
        }

        for(int i = 0; i < list.size(); i++ ){

            System.out.println(list.get(i));

        }
    }

    public void createNewFile(){

        try{
            File passwordFile = new File("passwordfile2.txt");
            passwordFile.createNewFile();
        } catch (IOException e){
            System.out.println(e);
        }
    }

    public void writeToFile(){

        try{
            BufferedWriter fileWriterBuffer = new BufferedWriter(fileWriter);

            for(int i = 0; i < list.size(); i++){
                fileWriterBuffer.write(list.indexOf(i));
                System.out.println(list.indexOf(i));
                fileWriterBuffer.newLine();
            }
            fileWriter.flush();
            fileWriter.close();

        } catch (IOException e){
            System.out.println(e);
        }
    }
}
