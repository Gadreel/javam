package com.divconq.test;

import com.divconq.gtm.JavaM;

public class Main {

	public static void main(String[] args) {
		if (args.length < 2) {
			System.out.println("Syntax: JavaM globalname [subscript1] [subscript2] ... [value]");
			System.out.println("For example to set ^x(\"2\",\"name\")=\"fred\" use JavaM ^x 2 name fred");
			return;
		}

		String globalName = args[0];
		
		if (args.length > 2) {
			globalName += "(";
					
			for (int i = 1; i < (args.length - 2); i++) {
				if (i > 1)
					globalName += ",";
					
				globalName += "\"" + args + "\""; 
			}
			
			globalName += ")";
		}
		
		JavaM.getInstance().SET(globalName, args[args.length - 1]);

		System.out.println("Echo:");
		System.out.println(JavaM.getInstance().GET(globalName));
	}
}
