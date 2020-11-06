package com.creativeTtech;
import java.util.*;

public class passwordContainer {

    public LinkedList<String> list = new LinkedList<>();

    public passwordContainer(){

        list.add("password");
        list.add("password 2");
    }



    void printList(LinkedList list){

        for(int i = 0; i < list.size(); i++ ){

            System.out.println(list.get(i));

        }
    }
}
