import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorldServlet extends HttpServlet {

    // Override the doGet method to handle GET requests
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        // Set the response content type to HTML
        response.setContentType("text/html");

        // Get the PrintWriter object to write HTML response
        PrintWriter out = response.getWriter();

        // Get the value of the 'name' parameter from the request
        String name = request.getParameter("name");

        // Write the HTML response
        out.println("<html><body>");
        out.println("<center><h1>Welcome, " + name + "</h1></center>");
        out.println("</body></html>");
    }
}
