package com.divconq.gtm;

public class JavaM {
	public static final int ORDER_FORWARD = 1;
	public static final int ORDER_BACKWARD = -1;

	// The native methods
	private synchronized native void GTMSET(String globalName, String value);

	private synchronized native void GTMSET(String[] globalNames, String[] values);

	private synchronized native String GTMGET(String globalName);

	private synchronized native void GTMKILL(String globalName);

	private synchronized native String GTMORDER(String globalName, int direction);

	private synchronized native String GTMQUERY(String globalName);

	private synchronized native String GTMINCREMENT(String globalName, int expr);

	private synchronized native void GTMTSTART();

	private synchronized native void GTMTCOMMIT();

	// Load the GTM_CI shared library
	static {
		try {
			System.loadLibrary("gtm_ci");
		} catch (Exception ex) {
			ex.printStackTrace();
			System.exit(1);
		}

	}

	private static JavaM instance = new JavaM();

	private JavaM() {
	}

	/**
	 * Return a GTM instance
	 * 
	 * @return
	 */
	public static JavaM getInstance()
	{
		return JavaM.instance;
	}

	/**
	 * 
	 * @param globalName
	 * @param value
	 */
	public void SET(String globalName, String value)
	{
		GTMSET(globalName, value);
	}

	/**
	 * 
	 * @param globalNames
	 * @param values
	 */
	public void SET(String[] globalNames, String[] values)
	{
		GTMSET(globalNames, values);
	}

	/**
	 * 
	 * @param globalName
	 * @return
	 */
	public String GET(String globalName)
	{
		return GTMGET(globalName);
	}

	/**
	 * Increment a long Create the global var if it doesn't exists
	 * 
	 * @param globalName
	 * @return the incremented value (1 for the first time)
	 */
	public long INCREMENT(String globalName)
	{
		return Long.parseLong(GTMINCREMENT(globalName, 1));
	}

	/**
	 * Decrement a long. Removes the global variable if the value is 0 after decrement
	 * 
	 * @param globalName
	 * @return
	 */
	public long DECREMENT(String globalName)
	{
		return Long.parseLong(GTMINCREMENT(globalName, -1));
	}

	/**
	 * 
	 * @param globalName
	 */
	public void KILL(String globalName)
	{
		GTMKILL(globalName);
	}

	/**
	 * 
	 * @param globalName
	 * @return
	 */
	public String ORDER(String globalName)
	{
		return GTMORDER(globalName, ORDER_FORWARD);
	}

	/**
	 * 
	 * @param globalName
	 * @param direction
	 * @return
	 */
	public String ORDER(String globalName, int direction)
	{
		return GTMORDER(globalName, direction);
	}

	/**
	 * 
	 * @param globalName
	 * @return
	 */
	public String QUERY(String globalName)
	{
		return GTMQUERY(globalName);
	}

	/**
	 * 
	 */
	public void TSTART()
	{
		GTMTSTART();
	}

	/**
	 * 
	 */
	public void TCOMMIT()
	{
		GTMTCOMMIT();
	}
}
