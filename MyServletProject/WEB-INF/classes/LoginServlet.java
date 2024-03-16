import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        // Forward the request to the login.html page
        request.getRequestDispatcher("/webapp/login.html").forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        // Retrieve username and password from request parameters
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Database connection information
        String url = "jdbc:mysql://localhost:3306/techhub";
        String dbUsername = "root";
        String dbPassword = "Saurabh@148";

        // SQL query to retrieve user's name
        String nameQuery = "SELECT firstname FROM registration WHERE firstname = ? AND password = ?";

        try {
            // Load the MySQL JDBC driver
            Class.forName("com.mysql.jdbc.Driver");

            // Establish the database connection
            try (Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword);
                    PreparedStatement statement = connection.prepareStatement(nameQuery)) {

                // Set parameters for the SQL query
                statement.setString(1, username);
                statement.setString(2, password);

                if (username == null || username.isEmpty() || password == null || password.isEmpty()) {
                    // Handle empty username or password
                    response.getWriter().println("Please provide both username and password.");
                    return;
                }

                // Execute the query to retrieve user's name
                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        String name = resultSet.getString("firstname");
                        // User exists, redirect to the welcome page passing the name
                        response.sendRedirect("hello?name=" + name);
                    } else {
                        // User does not exist or invalid credentials, display error message
                        response.getWriter().println("Invalid username or password.");
                    }
                }
            }
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
            response.getWriter().println("Database connection error (Login). Please try again later.");
        }
    }
}
