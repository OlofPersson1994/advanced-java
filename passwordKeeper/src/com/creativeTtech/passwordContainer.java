package com.creativeTtech;
import java.util.*;

public class passwordContainer {

    public LinkedList<String> list = new LinkedList<>();

    public passwordContainer(){


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
}
