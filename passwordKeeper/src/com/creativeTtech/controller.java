package com.creativeTtech;
import java.util.*;
public class controller {

    String inputPassword;
    String password = "password";
    String welcomeText = "Welcome to passwordKeeper\nChoose one of the following alternatives.";
    String option = ("1: Login\n2: Add new password");


    public controller() {

        passwordContainer passwordContainer = new passwordContainer();

        while (true) {
            System.out.println(welcomeText);
            System.out.println(option);

            Scanner menyScanner = new Scanner(System.in);

            int menyInput = menyScanner.nextInt();

            if (menyInput == 1) {

                System.out.println("Please put in the password:");

                menyScanner = new Scanner(System.in);

                inputPassword = menyScanner.nextLine();



                if (password.equals(inputPassword)) {

                    System.out.println("You are logged in.");

                    passwordContainer.printList(passwordContainer.list);

                } else {

                    System.out.println("Hard drive destroyed");
                }

            }
            if (menyInput == 2) {

                System.out.println("Put in the new password:");

                menyScanner = new Scanner(System.in);
                password = menyScanner.nextLine();

                System.out.println("The new password is: " + password);
            }
        }
    }
}

