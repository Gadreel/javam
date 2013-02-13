package com.divconq.gtm;

public class M {

	// The native methods
	private synchronized native void set(String name, String value);
	private synchronized native void kill(String name);
	private synchronized native String increment(String name, int amt);	
	private synchronized native void merge(String destName, String srcName);
	
	private synchronized native String get(String name);
	private synchronized native String data(String name);
	private synchronized native String next(String name);
	private synchronized native String previous(String name);
	private synchronized native String query(String name);
	
	private synchronized native String lock(String name);
	private synchronized native String unlock(String name);
	
	private synchronized native void tStart();
	private synchronized native void tCommit();
	private synchronized native void tRollback();
	
	private synchronized native String func(String name, String args);
	private synchronized native void proc(String name, String args);
	

	// Load the GTM_CI shared library
	static {
		try {
			System.loadLibrary("gtm_ci");
		} catch (Exception ex) {
			ex.printStackTrace();
			System.exit(1);
		}

	}

	public final static M instance = new M();

	private M() {
	}
	
	/**
	 * set a global (or local) with optional subscripts for example:
	 * 		M.instance.set("^x", "test1");
	 * results in
	 * 		s ^x="test1"
	 * 
	 * and
	 * 		M.instance.set("^x", "a", "1", "test2");
	 * results in
	 * 		s ^x("a",1)="test2"
	 * 
	 * @param path 		the path starts with the global name, then is followed by 
	 * 					0 or more subscripts and finally a value
	 */
	public void set(String... path) {
		this.set(this.toGlobalNameExpectValue(path), this.escapeValue(path[path.length - 1]));
	}

	/**
	 * set a global (or local) with optional subscripts for example:
	 * 		M.instance.get("^x");
	 * results in
	 * 		^x
	 * 
	 * and
	 * 		M.instance.get("^x", "a", "1");
	 * results in
	 * 		^x("a",1)
	 * 
	 * @param path 		the path starts with the global name, then is followed by 
	 * 					0 or more subscripts 
	 */
	public String get(String... path) {
		return this.get(this.toGlobalName(path));
	}

	/**
	 * Increment a global (or local)
	 * 
	 * @param path 		the path starts with the global name, then is followed by 
	 * 					0 or more subscripts 
	 * @return 			the incremented value (1 for the first time)
	 */
	public long inc(String... path) {
		return Long.parseLong(this.increment(this.toGlobalName(path), 1));
	}

	/**
	 * Decrement a global (or local)
	 * 
	 * @param path 		the path starts with the global name, then is followed by 
	 * 					0 or more subscripts 
	 * @return 			the decremented value 
	 */
	public long dec(String... path) {
		return Long.parseLong(this.increment(this.toGlobalName(path), -1));
	}

	/**
	 * Increment a global (or local)
	 * 
	 * @param amt		amount to increment by (may be negative)
	 * @param path 		the path starts with the global name, then is followed by 
	 * 					0 or more subscripts 
	 * @return 			the incremented value 
	 */
	public long inc(int amt, String... path) {
		return Long.parseLong(this.increment(this.toGlobalName(path), amt));
	}

	/**
	 * Remove a global and all its child nodes
	 * 
	 * @param path 		the path starts with the global name, then is followed by 
	 * 					0 or more subscripts 
	 */
	public void kill(String... path) {
		this.kill(this.toGlobalName(path));
	}

	/**
	 * Merge a source global with a target global (or locals)
	 * 
	 * @param dest 		the path starts with the global name, then is followed by 
	 * 					0 or more subscripts 
	 * @param src 		the path starts with the global name, then is followed by 
	 * 					0 or more subscripts 
	 */
	public void merge(String[] dest, String[] src) {
		this.merge(this.toGlobalName(dest), this.toGlobalName(src));
	}

	/**
	 * Loop to the next subscript (of the deepest subscript)
	 * 
	 * @param path 		the path starts with the global name, then is followed by 
	 * 					0 or more subscripts 
	 * @return			the value of the next subscript or null
	 */
	public String next(String... path) {
		return this.next(this.toGlobalName(path));
	}

	/**
	 * Loop to the previous subscript (of the deepest subscript)
	 * 
	 * @param path 		the path starts with the global name, then is followed by 
	 * 					0 or more subscripts 
	 * @return			the value of the previous subscript or null
	 */
	public String prev(String... path) {
		return this.prev(this.toGlobalName(path));
	}

	/**
	 * check for data in a sparse array (global or local)
	 * 
	 * @param path 		the path starts with the global name, then is followed by 
	 * 					0 or more subscripts 
	 * @return			ff = no data or children, ft = data but not children, tf = children but no data, tt = data and children
	 */
	public String data(String... path) {
		return this.data(this.toGlobalName(path));
	}

	/**
	 * Traverse the sparse array (global or local)
	 * 
	 * @param path 		the path starts with the global name, then is followed by 
	 * 					0 or more subscripts 
	 * @return			the full name of the next entry in the array 
	 */
	public String query(String... path) {
		return this.query(this.toGlobalName(path));
	}

	/**
	 * Traverse the sparse array (global or local)
	 * 
	 * @param name		the full name of the entry in the array to query from 
	 * @return			the full name of the next entry in the array 
	 */
	public String queryName(String name) {
		return this.query(name);
	}

	/**
	 *  start a transaction
	 */
	public void txStart() {
		this.tStart();
	}

	/**
	 * commit a transaction
	 */
	public void txCommit() {
		this.tCommit();
	}

	/**
	 * rollback a transaction
	 */
	public void txRollback() {
		this.tRollback();
	}

	/**
	 * Lock a sparse array (global or local)
	 * 
	 * @param path 		the path starts with the global name, then is followed by 
	 * 					0 or more subscripts 
	 * @return			the full name of the next entry in the array 
	 */
	public String lock(String... path) {
		return this.lock(this.toGlobalName(path));
	}

	/**
	 * Lock a sparse array (global or local)
	 * 
	 * @param name		the full name of the entry in the array to lock 
	 * @return			the full name of the next entry in the array 
	 */
	public String lockName(String name) {
		return this.lock(name);
	}

	/**
	 * Unlock a sparse array (global or local)
	 * 
	 * @param path 		the path starts with the global name, then is followed by 
	 * 					0 or more subscripts 
	 * @return			the full name of the next entry in the array 
	 */
	public String unlock(String... path) {
		return this.unlock(this.toGlobalName(path));
	}

	/**
	 * Unlock a sparse array (global or local)
	 * 
	 * @param name		the full name of the entry in the array to unlock 
	 * @return			the full name of the next entry in the array 
	 */
	public String unlockName(String name) {
		return this.unlock(name);
	}

	/**
	 * Call a function - must have parameters and must return something
	 * 
	 * @param name		the full name of the code to execute (e.g. "tag^routine")
	 * @param args		arguments to the function 
	 * @return			the return value from the function
	 */
	public String funcCall(String name, String...  args) {
		return this.func(name, this.toGlobalName(args));
	}

	/**
	 * Call a procedure - must have parameters and must not return something
	 * 
	 * @param name		the full name of the code to execute (e.g. "tag^routine") 
	 * @param args		arguments to the procedure
	 */
	public void procCall(String name, String...  args) {
		this.proc(name, this.toGlobalName(args));
	}
	
	/**
	 * Pull the global name form an array of strings
	 * 
	 * @param args 	The global name and optional subscripts
	 * @return		The global name assembled for use within M
	 */
	protected String toGlobalName(String... args) {
		if ((args == null) || (args.length < 1))
			throw new IllegalArgumentException("Missing global name");

		String globalName = args[0];
		
		if (args.length > 1) {
			globalName += "(";
					
			for (int i = 1; i < (args.length); i++) {
				if (i > 1)
					globalName += ",";
					
				if (args[i] == null)
					globalName += "null";
				else
					globalName += "\"" + args[i].replace("\"", "\"\"") + "\""; 
			}
			
			globalName += ")";
		}

		return globalName;
	}
	
	/**
	 * Pull the global name form an array of strings, assume the last String is the value not part of the global
	 * 
	 * @param args 	The global name and optional subscripts, plus a value
	 * @return		The global name assembled for use within M
	 */
	protected String toGlobalNameExpectValue(String... args) {
		if ((args == null) || (args.length < 2))
			throw new IllegalArgumentException("Missing global name or value");

		String globalName = args[0];
		
		if (args.length > 2) {
			globalName += "(";
					
			for (int i = 1; i < (args.length - 1); i++) {
				if (i > 1)
					globalName += ",";
					
				// escape the subscripts
				if (args[i] == null)
					globalName += "null";
				else
					globalName += "\"" + args[i].replace("\"", "\"\"") + "\""; 
			}
			
			globalName += ")";
		}

		return globalName;
	}

	/**
	 * Escape a value for use in M
	 * 
	 * @param value  	to escape
	 * @return			escaped value
	 */
	protected String escapeValue(String value) {
		if (value == null) 
			return value;
		
		return value.replace("\"", "\"\"");
	}
}
