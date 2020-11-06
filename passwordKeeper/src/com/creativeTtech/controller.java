package com.creativeTtech;

import java.util.*;

public class controller {

    public controller() {
        String testPassword;
        String theFirstPassWord = "password";

        String welcomeText = "Welcome to passwordKeeper\nChoose one of the following alternatives.";
        String option = ("1: Login\n2: Add new password");

        while (true) {
            System.out.println(welcomeText);
            System.out.println(option);

            Scanner inputScanner = new Scanner(System.in);

            int inputFromUser = inputScanner.nextInt();

            inputScanner = new Scanner(System.in);
            if (inputFromUser == 1) {

                System.out.println("Please put in the password:");

                testPassword = inputScanner.nextLine();

                if (theFirstPassWord.equals(testPassword)) {

                    System.out.println("You are logged in.");
                } else {

                    System.out.println("Hard drive destroyed");
                }

            }
            if (inputFromUser == 2) {

                System.out.println("Put in the new password:");

                inputScanner = new Scanner(System.in);
                theFirstPassWord = inputScanner.nextLine();

                System.out.println("The new password is: " + theFirstPassWord);
            }
        }
    }
}

