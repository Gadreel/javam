package com.divconq.test;

import java.util.Scanner;

import com.divconq.gtm.M;

public class Main {

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		
		System.out.println("Set tests: ");
		
		M.instance.kill("^xyz");
		
		M.instance.set("^xyz", "a", "b", "c", "bottom");
		M.instance.set("^xyz", "top");

		System.out.println("Data 1a (expect 'ft'): " + M.instance.data("^xyz", "a", "b", "c"));
		System.out.println("Get 1a (expect 'bottom'): " + M.instance.get("^xyz", "a", "b", "c"));
		
		System.out.println("Data 1b (expect 'tf'): " + M.instance.data("^xyz", "a", "b"));
		System.out.println("Get 1b (expect null): " + M.instance.get("^xyz", "a", "b"));
		
		System.out.println("Data 1c (expect 'tt'): " + M.instance.data("^xyz"));
		System.out.println("Get 1c (expect 'top'): " + M.instance.get("^xyz"));
		
		System.out.println("Data 1d (expect 'ff'): " + M.instance.data("^xyzzzz"));
		System.out.println("Get 1d (expect null): " + M.instance.get("^xyzzzz"));		
		
		System.out.println();
		
		System.out.println("Enter to continue.");
		s.nextLine();
		
		M.instance.set("^xyz", "a", "b", "d", "carrot");
		M.instance.set("^xyz", "a", "b", "e", "tomato");
		M.instance.set("^xyz", "a", "b", "f", "celery");
		
		String i = M.instance.next("^xyz", "a", "b", null);
		
		System.out.println("order (expect c, d, e, f)");
		
		while (i != null) {
			System.out.println("\tfound: " + i);
			i = M.instance.next("^xyz", "a", "b", i);
		}
		
		System.out.println();
		
		System.out.println("Enter to continue.");
		s.nextLine();
		
		M.instance.inc(12, "^xyz", "0");
		
		System.out.println("From inc, expect 12: " + M.instance.get("^xyz", "0"));
		
		M.instance.dec("^xyz", "0");
		
		System.out.println("From dec, expect 11: " + M.instance.get("^xyz", "0"));
		
		System.out.println("Enter to continue.");
		s.nextLine();
		
		M.instance.kill("^xyz");
		System.out.println("Kill (expect 'ff'): " + M.instance.data("^xyz"));
		
		System.out.println("Enter to continue.");
		s.nextLine();
		
		System.out.println("Func call (expect 'hello world'): " + M.instance.funcCall("echo^gtmjni", "hello world"));
		
		System.out.println("Enter to continue.");
		s.nextLine();
		
		System.out.println("Proc call");
		
		M.instance.procCall("ping^gtmjni", "hello world");
		
		System.out.println("Done!");
	}
}
