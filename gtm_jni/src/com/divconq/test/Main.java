package com.divconq.test;

import com.divconq.gtm.M;

public class Main {

	public static void main(String[] args) {
		M.instance.set("^xyz", "a", "b", "c", "here");

		System.out.println("Echo:");
		System.out.println(M.instance.get("^xyz", "a", "b", "c", "here"));
	}
}
