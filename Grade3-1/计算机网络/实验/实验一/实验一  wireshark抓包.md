# 实验一  wireshark抓包

## 一、实验目的

通过本实验，熟练掌握Wireshark的操作和使用，学习对HTTP、TCP等协议进行分析。

## 二、实验要求

安装完Wireshark后任选两个实验完成,要求实验不能是同一章中的内容。安装文档和实验内容详见文档。

## 三、实验内容

### Ethereal Lab: HTTP

#### 实验任务

在本实验中，我们将探索HTTP协议的几个方面：基本的GET/响应交互、HTTP消息格式、检索大型HTML文件、检索带有嵌入式对象的HTML文件以及HTTP身份验证和安全性。

#### 实验步骤

##### **1、The Basic HTTP GET/response interaction** 

让我们通过下载一个非常简单的 HTML 文件来开始探索 HTTP —— 这个文件非常短，并且不包含嵌入的对象。

1. 启动网页浏览器。

2. 启动Wireshark数据包嗅探器，但不要开始捕获数据包。在过滤器中输入http过滤非HTTP数据报文，捕获的HTTP数据报文稍后将显示在数据包列表窗口中。（我们只对这里的HTTP协议感兴趣，不想看到所有捕获杂乱无章的数据包）。

   ![截屏2024-11-08 下午5.14.00](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-08 下午5.14.00.png)

3. 等待一分钟以上，然后开始捕获数据包。

4. 在浏览器中输入以下内容

   `http://gaia.cs.umass.edu/ethereal-labs/HTTP-ethereal-file1.html`

   浏览器应该显示非常简单的单行HTML文件。

   ![截屏2024-11-08 下午5.16.22](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-08 下午5.16.22.png)

5. 停止抓包。

最终显示在数据包列表窗口中的数据包为

![截屏2024-11-08 下午5.21.16](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-08 下午5.21.16.png)

数据包列表窗口中显示捕获了两条HTTP报文：GET报文（从本地浏览器到gaia.cs.umass.edu网络服务器）和从服务器到本地浏览器的响应报文。数据包内容窗口显示所选报文的详细信息（图中是HTTP GET报文，在数据包列表窗口中高亮显示）。

由于HTTP报文封装在TCP段中，会携带TCP头部信息，TCP段封装IP数据报中，该段携带IP头部信息，IP数据报封装在太网帧中，IP头部信息，所以Wireshark也会显示帧、以太网、IP和TCP的数据包信息。

这里我们仅对HTTP感兴趣，因此在数据包内容窗口中我们只显示HTTP报文（HTTP行右边的箭头朝下，说明显示所有详细信息），其他帧、以太网、IP和TCP信息隐藏（右边箭头朝右，说明隐藏详细信息）。

通过查看HTTP GET报文和响应报文中的信息，回答以下问题。在回答以下问题时，打印出GET和响应报文，并在报文中注明在哪里找到以下问题的答案。 

1. **Is your browser running HTTP version 1.0 or 1.1? What version of HTTP is the server running?** 

   二者都是HTPP1.1

   我的浏览器：

   ![截屏2024-11-09 上午10.05.35](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-09 上午10.05.35.png)

   服务器：

   ![截屏2024-11-09 上午10.05.15](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-09 上午10.05.15.png)

2. **What languages (if any) does your browser indicate that it can accept to the server?** 

   ![截屏2024-11-09 上午10.06.27](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-09 上午10.06.27.png)

3. **What is the IP address of your computer? Of the gaia.cs.umass.edu server?** 

   我的电脑：10.69.143.43

   gaia.cs.umass.edu 服务器：128.119.245.12

   ![截屏2024-11-09 上午10.12.46](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-09 上午10.12.46.png)

4. **What is the status code returned from the server to your browser?** 

   304 Not Modified， 它表示客户端请求的资源没有发生变化，因此服务器不需要重新发送资源的内容（因为第一次下载html文件时未截图，服务器第一次返回的状态码是200 OK，表示服务器正确返回请求资源内容）![截屏2024-11-09 上午10.15.02](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-09 上午10.15.02.png)![截屏2024-11-09 上午10.55.28](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-09 上午10.55.28.png)

5. **When was the HTML file that you are retrieving last modified at the server?** 

   2024年11月8日 06:59:01 GMT

   ETag 是资源的实体标签，用来标识资源的版本。它是由服务器生成的唯一标识符。客户端在下次请求时可通过 If-None-Match 头字段发送 ETag 值，服务器对比后判断资源是否变化。

   服务器返回的ETag头为**7e-62661492e0fdc**

   ![截屏2024-11-09 上午10.43.18](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-09 上午10.43.18.png)

   我的浏览器获取html文件的版本和记录的资源最后修改时间是2024年11月8日 06:59:01 GMT

   ![截屏2024-11-09 上午10.39.19](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-09 上午10.39.19.png)

   所以可以认为 HTML 文件的最后修改时间是 2024年11月8日 06:59:01 GMT 或更早。

   更新缓存后再抓包，成功返回200状态码后查看响应报文Last-Modified字段可发现HTML 文件的最后修改时间确实是 2024年11月8日 06:59:01 GMT，也就是我第一次下载html文件的时间。![截屏2024-11-09 上午10.56.03](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-09 上午10.56.03.png)

6. **How many bytes of content are being returned to your browser?** 

   从Content-Length字段可知，返回的内容字节大小为126字节

   ![截屏2024-11-09 上午10.57.53](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-09 上午10.57.53.png)

7. **通过检查数据包内容窗口中的原始数据，在数据包列表窗口中是否有未显示的数据标头？如果是这样，请说出一个。**

   Line-based text data，可以看到数据包内容中还有一个Line-based text data数据报文，但在数据包列表窗口中并未显示，这个应该是响应报文中的实体主体。

   ![截屏2024-11-09 上午11.01.59](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-09 上午11.01.59.png)

##### **2、The HTTP CONDITIONAL GET/response interaction **

回想第2.2.5节，大多数Web浏览器执行对象缓存，因此在检索HTTP对象时执行有条件的GET。在执行以下步骤之前，请确保浏览器缓存为空。现在做以下操作：

- 如上所述，启动您的网页浏览器，并确保浏览器的缓存已清除。

- 启动Wireshark数据包嗅探器

- 在浏览器中输入以下URL

  http://gaia.cs.umass.edu/ethereal-labs/HTTP-ethereal-file2.html 
  浏览器应该显示一个非常简单的五行HTML文件。 

- 快速在浏览器中再次输入相同的URL（或只需选择浏览器上的刷新按钮）

- 停止数据包捕获，并在显示过滤器规格窗口中输入“http”，以便稍后仅捕获的HTTP消息显示在数据包列表窗口中。


8. **Inspect the contents of the first HTTP GET request from your browser to the server. Do you see an “IF-MODIFIED-SINCE” line in the HTTP GET? **

   如上节一样，清空浏览器缓存后，如果多次向服务器发送相同请求报文，除了第一次服务器返回的响应报文状态码为`200 OK`，后面的响应报文状态码均为`304 Not Modified`。可以在HTTP GET 请求中看到 “IF-MODIFIED-SINCE” 行。

   ![截屏2024-11-11 下午4.58.44](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-11 下午4.58.44.png)

9. **Inspect the contents of the server response. Did the server explicitly return the contents of the file? How can you tell? **

   第一次响应报文服务器返回了完整的文件内容，因为其状态码为`200 OK`，且能在响应报文中Content-Length行中知道返回文件的大小，从Line-based text data行中看到文件内容，而第二次响应报文服务器没有返回文件内容，而是让浏览器使用缓存的内容，因为其状态码为`304 Not Modified`，并且其响应报文没有Content-Length和Line-based text data行。

   第一个HTTP响应报文：

   ![截屏2024-11-11 下午5.07.41](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-11 下午5.07.41.png)

   第二个HTTP响应报文：

   ![截屏2024-11-11 下午5.08.34](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-11 下午5.08.34.png)

10. **Now inspect the contents of the second HTTP GET request from your browser to the server. Do you see an “IF-MODIFIED-SINCE:” line in the HTTP GET? If so, what information follows the “IF-MODIFIED-SINCE:” header? **

    可以在第二个HTTP GET请求报文中看到**IF-MODIFIED-SINCE**字段，该头部信息为浏览器上次缓存该资源（即本次实验的html文件）的时间。这个时间戳用于告知服务器浏览器缓存的资源的最后修改时间。服务器接收到这个请求后会根据该时间戳判断资源是否有更新。

    ![截屏2024-11-11 下午4.58.44](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-11 下午4.58.44.png)

11. **What is the HTTP status code and phrase returned from the server in response to this second HTTP GET? Did the server explicitly return the contents of the file? Explain. **

    服务器在响应第二个 HTTP GET 请求时返回的 HTTP 状态码和方法字段是`304 Not Modified`，服务器并没有返回文件的内容，原因是浏览器第一次向服务器发送HTTP GET请求时会缓存服务器返回的文件内容，浏览器第二次再向服务器发送请求时，服务器只会让浏览器使用上次的缓存内容，不会返回文件内容，因为文件内容没有被更新。

    ![截屏2024-11-11 下午5.27.17](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-11 下午5.27.17.png)


##### 3、Retrieving Long Documents 

在我们之前的示例中，检索到的文档都是简单且较短的 HTML 文件。接下来，让我们看看下载一个较长的 HTML 文件时会发生什么。

执行以下步骤：

- 启动您的网络浏览器，并确保浏览器的缓存已清除（如上所述）。

- 启动 Ethereal（现称为 Wireshark）数据包嗅探器。

- 在浏览器中输入以下 URL：
  - [http:*//gaia.cs.umass.edu/ethereal-labs/HTTP-ethereal-file3.html*](http://gaia.cs.umass.edu/ethereal-labs/HTTP-ethereal-file3.html)
  - 浏览器应显示内容较长的美国《权利法案》。

- 停止 Ethereal 的数据包捕获，并在显示过滤器窗口中输入“http”，这样只会显示捕获的 HTTP 消息。

在数据包列表窗口中，应该能看到浏览器 HTTP GET 请求消息，接着是对该 HTTP GET 请求的多包响应。这个多包响应值得一些解释。回顾第 2.2 节（参见图 2.9）中提到的内容：HTTP 响应消息包含**状态行**、**首部行**、一个**空行**，以及**实体体**。在我们的 HTTP GET 请求的情况下，响应中的实体主体是*整个*被请求的 HTML 文件。在我们的例子中，HTML 文件相当长，大小为 4500 字节，无法装入一个 TCP 数据包中。因此，单一的 HTTP 响应消息被 TCP 分成了多个片段，每个片段包含在一个独立的 TCP 段中（参见图 1.22）。每个 TCP 段在 Wireshark 中记录为一个独立的数据包，而单个 HTTP 响应被分成多个 TCP 数据包的事实则通过 Whireshark 显示的 “Continuation”（继续）字样来指示。需要强调的是，HTTP 中并没有“Continuation”消息！

![截屏2024-11-11 下午8.46.40](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-11 下午8.46.40.png)

回答以下问题：

12. **How many HTTP GET request messages were sent by your browser? **

    可以看到浏览器只发送了一个HTTP GET请求报文

    ![截屏2024-11-11 下午8.47.57](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-11 下午8.47.57.png)
13. **How many data-containing TCP segments were needed to carry the single HTTP response? **

    传输一个HTTP响应报文需要5个含数据的TCP段

    ![截屏2024-11-11 下午8.49.13](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-11 下午8.49.13.png)

14. **What is the status code and phrase associated with the response to the HTTP GET request? **

    响应报文的状态码和短语为`200 OK`

    ![截屏2024-11-11 下午8.58.05](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-11 下午8.58.05.png)

15. **Are there any HTTP status lines in the transmitted data associated with a TCP-induced “Continuation”? **

    在与 TCP 引起的“Continuation”相关的传输数据中没有任何 HTTP 状态行。完整的 HTTP 状态行（如 HTTP/1.1 200 OK）一般只出现在第一个 TCP 数据包中，后续的 TCP 包则仅包含响应的实体内容，没有重复的 HTTP 状态行或头部信息。通过响应报文可知传输该响应报文的TCP数据包为105、106、107、108、109号数据包(13问），分别查看其数据内容，可以发现只有第一个TCP数据包携带了HTTP状态行信息。

    ![截屏2024-11-11 下午9.18.37](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-11 下午9.18.37.png)

##### 4、HTML Documents with Embedded Objects

现在我们已经了解了 Wireshark 如何显示大型 HTML 文件的捕获数据流量，现在可以看看当浏览器下载包含嵌入对象的文件时会发生什么。例如，下文的例子中，文件包含存储在其他服务器上的对象（如图像文件）。

执行以下操作：

- 启动Web浏览器，并确保浏览器的缓存已清除。
- 启动 Wireshark 数据包嗅探器。
- 在浏览器中输入以下 URL：
  - http://gaia.cs.umass.edu/ethereal-labs/HTTP-ethereal-file4.html
  - 浏览器应显示一个包含两个图像的简短 HTML 文件。这两个图像被引用在基础的 HTML 文件中。也就是说，图像本身不在 HTML 中，而是图像的 URL 包含在下载的 HTML 文件中。如教材中讨论的那样，浏览器需要从指定的网站中检索这些图标。书的出版商的图标从 www.awl.com 网站检索，书的封面图像存储在 manic.cs.umass.edu 服务器上。
  
  因为某种原因第一幅图片没有加载出来，说明浏览器没能从指定的网站（这里应该是 www.awl.com 获取图片资源），书的封面正查显示。
  
  ![截屏2024-11-11 下午9.35.11](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-11 下午9.35.11.png)
- 停止 Wireshark 数据包捕获，并在显示过滤器指定窗口中输入“http”，以便仅显示捕获的 HTTP 消息。

以下是抓取到的数据列表，可以看到其中一个HTTP响应报文的状态码和短语是`403 Forbidden`

![截屏2024-11-12 上午10.34.58](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-12 上午10.34.58.png)

这里就能知道浏览器没有加载出来第一幅图片的可能原因：

- **访问权限限制**：服务器设置了访问控制，限制某些 IP 地址或用户访问此资源。
- **目录禁止访问**：服务器未配置自动目录列表，导致没有权限直接访问 URL。
- **文件权限问题**：服务器上的文件或目录权限配置不允许外部访问。
- **防火墙或其他安全措施**：某些服务器会使用防火墙、反爬虫等工具限制访问，尤其是从未知来源的请求。

回答以下问题：

16. **How many HTTP GET request messages were sent by your browser? To which Internet addresses were these GET requests sent?**

    我的浏览器发送了3个HTTP GET请求报文，它们发送的服务器地址分别是

    1. IP地址：128.110.245.12	URL：http://gaia.cs.umass.edu/ethereal-labs/HTTP-ethereal-file4.html

       ![截屏2024-11-12 上午10.38.33](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-12 上午10.38.33.png)

    2. IP地址：52.51.131.59		URL：http://www.aw-bc.com/catalog/images/pearson-logo-footer.gif

       ![截屏2024-11-12 上午10.17.03](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-12 上午10.53.43.png)
    3. IP地址：128.110.245.12	URL：http://manic.cs.umass.edu/~kurose/cover.jpg

       ![截屏2024-11-12 上午10.56.04](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-12 上午10.56.04.png)
17. **Can you tell whether your browser downloaded the two images serially, or whether they were downloaded from the two web sites in parallel? Explain. **

    浏览器是并行下载两个图片的，可以看到获取两个图片HTTP GET请求的请求时间分别是13.313283和13.368343，二者间隔在55ms左右，可以认为这两个请求是同时发起的，并且两个HTTP GET请求都建立了各自的TCP连接，且两个TCP连接中浏览器使用的端口号不同，所以可以认为浏览器是并行下载两幅图片的。

    两个HTTP请求的时间戳

    ![截屏2024-11-12 上午11.10.01](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-12 上午11.10.01.png)

    二者建立的TCP连接：

    请求第一幅图片使用的端口号是**64699**

    ![截屏2024-11-12 上午11.13.05](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-12 上午11.13.05.png)

    请求第二幅图片的端口号是**64700**

    ![截屏2024-11-12 上午11.13.05](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-12 上午11.13.40.png)

    

##### 5、 HTTP Authentication

最后，让我们尝试访问一个受密码保护的网站，并检查该站点交换的 HTTP 消息序列。

URL http://gaia.cs.umass.edu/ethereal-labs/protected_pages/HTTP-ethereal-file5.html 是受密码保护的。用户名为“eth-students”（不含引号），密码为“networks”（同样不含引号）。让我们访问这个“安全”的受密码保护的站点。

执行以下操作：

- 确保浏览器的缓存已清除，如上所述，然后关闭浏览器。接着，重新启动浏览器。

- 启动 Wireshark 数据包嗅探器。

- 在浏览器中输入以下 URL：
  - http://gaia.cs.umass.edu/ethereal-labs/protected_pages/HTTP-ethereal-file5.html
  - 在弹出的对话框中输入请求的用户名（eth-students）和密码（networks）。

- 停止 Ethereal 数据包捕获，并在显示过滤器指定窗口中输入“http”，这样稍后在数据包列表窗口中只会显示捕获的 HTTP 消息。

现在让我们检查 Wireshark 的输出。

![截屏2024-11-12 下午9.03.22](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-12 下午9.03.22.png)

这里因为抓包发现服务器始终返回的是`401 Unathorization`，多次尝试输入用户名和密码都不能访问html，故使用实验提供的抓包文件。

回答以下问题

18. **What is the server’s response (status code and phrase) in response to the initial HTTP GET message from your browser? **

    服务器响应第一个HTTP GET报文的状态码和短语是`401 Authorization Required`.

    ![截屏2024-11-12 下午9.06.36](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-12 下午9.06.36.png)

19. **When your browser’s sends the HTTP GET message for the second time, what new field is included in the HTTP GET message? **

    当浏览器第二次发起HTTP GET请求报文时，还包含了Authorization字段，其中可以看到输入的用户名和密码字段。

    ![截屏2024-11-12 下午9.08.24](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-12 下午9.08.24.png)




### Ethereal Lab: TCP

#### 实验任务

在这个实验里，我们将详细调查TCP的行为。我们将通过分析将150KB文件（包含Lewis Carrol的《爱丽丝梦游仙境》文本）从我们的计算机传输到远程服务器时发送和接收的TCP段的痕迹来做到这一点。我们将研究TCP使用序列和确认编号来提供可靠的数据传输；我们将看到TCP的拥塞控制算法——缓慢启动和避免拥塞——执行；我们将研究TCP的接收器广告流量控制机制。我们还将简要考虑TCP连接设置，并研究我们计算机和服务器之间TCP连接的性能（吞吐量和往返时间）

#### 实验步骤

#### 1、Capturing a bulk TCP transfer from your computer to a remote server 

在开始探索TCP之前，我们需要使用Wireshark来获取TCP将文件从您的计算机传输到远程服务器的数据包跟踪。我们通过访问一个网页来做到这一点，该网页将允许输入存储在计算机上的文件名（其中包含爱丽丝梦游仙境的ASCII文本），然后使用HTTP POST方法将文件传输到Web服务器。我们使用POST方法而不是GET方法，因为我们希望将大量数据从我们的计算机传输到另一台计算机。当然，在此期间，我们将运行Wireshark，以获取从我们的计算机发送和接收的TCP段的跟踪。

完成一下步骤：

- 获取《爱丽丝梦游仙境》的副本

  `http://gaia.cs.umass.edu/ethereal-labs/alice.txt`

  将此文件保存到计算机上。

- 接下来访问` http://gaia.cs.umass.edu/ethereal-labs/TCP-ethereal-file1.html `

- 应该看到一个看起来像这样的界面：![截屏2024-11-09 上午11.32.21](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-09 上午11.32.21.png)

- 使用此表单中的“选择文件”按钮在电脑中选择alice.txt。但先不要点击“Upload alice.txt file”按钮。

- 现在使用Wireshark开始数据包捕获

- 返回浏览器，按“上传alice.txt文件”按钮将文件上传到`gaia.cs.umass.edu`服务器。文件上传后，浏览器窗口中将显示一条简短的祝贺信息。

  ![截屏2024-11-09 上午11.37.07](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-09 上午11.37.07.png)

- 停止捕获。Wiresharl窗口应该与下面显示的窗口相似。


#### 2、 A first look at the captured trace

在详细分析TCP连接的行为之前，我们先从整体上对该跟踪进行一个概览。首先，通过在Wireshark窗口顶部的显示过滤器规范窗口中输入`“tcp”`来过滤Wireshark窗口中显示的数据包。应该看到的是计算机和`gaia.cs.umass.edu`之间的一系列TCP和HTTP消息并且会看到包含SYN消息的初始三次握手。

应该可以看到一条HTTP POST报文和一系列从我们的计算机发送到`gaia.cs.umass.edu`的“HTTP POST”报文。回忆我们在之前的 HTTP Ethereal 实验中讨论的内容，即不存在“HTTP POST”消息——这是 Ethereal 用来表示多个 TCP 段被用于传输单个 HTTP 消息的方式。

还会看到从` gaia.cs.umass.edu `返回到我们的计算机的 TCP ACK 段。

在回答问题时，尽量提供用于回答该问题的跟踪中的数据包打印输出。对打印输出进行注释以解释答案。

（要打印一个数据包内容，使用 *File->Print*，选择 *Selected packet only*，选择 *Packet summary line*，并选择回答问题所需的最小数据包细节）

由于此实验主要是关于 TCP 而非 HTTP，我们可以调整 Wireshark 的“捕获的数据包列表”窗口，使其显示包含 HTTP 消息的 TCP 段信息，而非 HTTP 消息本身的信息。要进行此设置，在 Wireshark 中选择 *Analyze->Enabled Protocols.*，然后取消勾选 HTTP 选项并选择 *OK*。此外，在此实验中，我们希望查看 TCP 的实际序列号（而非 Wireshark 可能默认显示的相对序列号）。为此，前往 *Edit->Preferences->Protocols->IP*，取消勾选“relative sequence numbers”选项。现在，你应会看到如下所示的 Wireshark 窗口：

![截屏2024-11-12 下午9.36.02](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-12 下午9.36.02.png)

#### 3、TCP Basics 

请回答以下有关 TCP 段的问题：

1. **你的客户端计算机（源）用于向**` gaia.cs.umass.edu` **传输文件的 IP 地址和 TCP 端口号是什么？**`gaia.cs.umass.edu` **用于接收文件的 IP 地址和端口号是什么？**

   通过观察HTTP POST请求报文，可知：

   客户端向服务器传输文件的IP地址是10.63.81.27，TCP端口号是58990

   服务器主机接受文件的IP地址是128.119.245.12，端口号是80

   ![截屏2024-11-12 下午10.46.31](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-12 下午10.46.31.png)

2. **用于建立客户端计算机和** `gaia.cs.umass.edu` **之间 TCP 连接的 SYN 段的序列号是什么？该段中的哪个部分标识了它是一个 SYN 段？**

   用于建立客户端和服务器之间的TCP连接的SYN的相对序列号是0，实际序列号是2626904640

   该段TCP头部的 Flags 字段中SYN标志位为1，标识了它是一个SYN段

   通过浏览捕捉的数据包列表，找到TCP3次握手建立连接的数据包：

   ![截屏2024-11-12 下午10.54.59](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-12 下午10.54.59.png)

3. **gaia.cs.umass.edu 发送给客户端计算机的 SYNACK 段的 序列号 是多少？该 SYNACK 段中的 ACK 字段的值是多少？gaia.cs.umass.edu是如何确定该值的？该段中的哪个部分标识了它是一个 SYNACK 段？**

   服务器主机发送的 SYNACK 段的相对序列号是0，实际序列号是2225400986

   该SYNACK段中的ACK字段的相对值为1，实际值为2626904641，服务器是通过接收到的客户端 SYN 包中的序列号确定ACK的值的，第2问中客户端向服务器发起TCP连接请求的SYN的相对序列号是0，实际序列号是2626904640，服务器会返回ACK = Seq + 1给客户端告知自己收到了SYN包。

   该段中的Flag字段中Ack和Syn标志位为1，标识了它是一个SYNACK段。

   ![截屏2024-11-12 下午11.21.58](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-12 下午11.21.58.png)

4. **包含 HTTP POST 命令的 TCP 段的序列号是多少？请注意，为了找到 POST 命令，你需要深入到 Wireshark 窗口底部的数据包内容区域，寻找数据字段中包含“POST”的段。**

   包含 HTTP POST 命令的 TCP 段的序列号是151818

   ![截屏2024-11-09 下午12.07.34](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-09 下午12.07.34.png)

   ![截屏2024-11-09 下午12.08.35](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-09 下午12.08.35.png)

5. **将包含 HTTP POST 的 TCP 段视为该 TCP 连接的第一个段。TCP 连接中前六个段的序列号分别是多少（包括包含 HTTP POST 的段）？每个段的发送时间是什么？每个段的 ACK 接收时间是什么？根据每个 TCP 段的发送时间与其确认接收时间的差值，计算每个段的 RTT 值。在每次接收到 ACK 后的 EstimatedRTT 值是多少（参考教材第 237 页）？假设第一个段的 EstimatedRTT 等于测量的 RTT 值，然后使用教材第 237 页的 EstimatedRTT 公式计算其余段的 EstimatedRTT。*注意：选择“listing of captured packets”窗口中从客户端发送到 `gaia.cs.umass.edu` 服务器的一个 TCP 段。然后选择：*`Statistics->TCP Stream Graph->Round Trip Time Graph.`* **

   从HTTP POST请求报文内容可知TCP连接中前六个段是62～67

   ![截屏2024-11-13 下午2.36.47](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-13 下午2.36.47.png)

   通过分别查看其报文，可得

   | TCP段 | 序列号（相对） | 发送时间(s) | ACK接收时间(s) | RTT      | EstimatedRTT(α = 0.125) |
   | ----- | -------------- | ----------- | -------------- | -------- | ----------------------- |
   | 1     | 1              | 2.657890    | 2.923113       | 0.265233 | 0.265233                |
   | 2     | 711            | 2.658640    | 2.923114       | 0.264474 | 0.265138                |
   | 3     | 1911           | 2.658644    | 2.923114       | 0.264470 | 0.265055                |
   | 4     | 3111           | 2.658648    | 2.923114       | 0.264466 | 0.264981                |
   | 5     | 4311           | 2.658652    | 2.923114       | 0.264462 | 0.264916                |
   | 6     | 5511           | 2.658655    | 2.923114       | 0.264459 | 0.264859                |

   使用Wireshark查看TCP连接的前六个段的RTT图：

   ![截屏2024-11-13 下午3.33.19](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-13 下午3.33.19.png)

6. **前六个 TCP 段的长度是多少？**

   710、1200、1200、1200、1200、1200

   ![截屏2024-11-13 下午3.51.57](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-13 下午3.51.57.png)

7. **在整个数据包追踪中，接收端所宣布的可用缓冲区的最小空间是多少？接收端缓冲区空间的不足是否曾经限制过发送端的传输速度？**

   可用缓冲区的最小空间是**30720Byte** ,在 Wireshark 中，选择 **Statistics** > **TCP Stream Graphs** > **Window Scaling Graph**，可查看接收端窗口大小随时间的变化。

   ![截屏2024-11-13 下午4.51.48](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-13 下午4.51.48.png)

   从I/O图来看，接收端缓冲区空间的不足曾经限制过发送端的传输速度，可以看到I/O速率有不同的峰值

   ![截屏2024-11-13 下午4.58.11](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-13 下午4.58.11.png)

8. **数据包追踪文件中是否有重传的段？您在追踪中检查了哪些内容以回答该问题？**

   没有重传的段，可以在数据包窗口列表中的Info列查找是否存在**TCP Dup ACK**或**TCP Retransmission**标签，通过查找只到了**TCP Dup ACK**，服务器续发送多个重复的 ACK给客户端，说明服务器没有收到某个预期的数据包，但并没有重传的TCP标签

   ![截屏2024-11-13 下午5.21.54](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-13 下午5.21.54.png)

9. **该 TCP 连接的吞吐量是多少（每单位时间传输的字节数）？请解释您是如何计算该值的。**

   首先查看整个TCP连接传输的字节数，可以通过**Statistics** > **Coversations** 获取客户端和服务器TCP连接传输的字节数为**164kB**

   ![截屏2024-11-13 下午7.11.12](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-13 下午7.11.12.png)

   再通过数据包列表计算TCP连接的传输时间，即从TCP 流的第一个数据包（包含 HTTP POST 请求的第一个 TCP 段）到最后一个数据包（通常是包含服务器的响应的时间）的传输时间

   TCP流传输第一个数据包的时间为2.657890

   ![截屏2024-11-13 下午7.38.51](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-13 下午7.38.51.png)

   服务器的响应的时间为3.725892

   ![截屏2024-11-13 下午7.53.31](/Users/fanglunlin/Library/Application Support/typora-user-images/截屏2024-11-13 下午7.53.31.png)

   计算吞吐量

   ​	吞吐量 = 164kB / (3.725892 - 2.657890) ≈ 153.5578 kB / s
