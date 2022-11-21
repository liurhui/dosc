#### DOM操作
##### 架构
	Domument  -> HTML / XML （标签）
	Element  -> HTML E  -> DIVE / ImageE   ... （标签事件）
	CharacterData  -> Text（ 字符数据：标签的文本）/ Comment（注释的标签）  
	Attr（标签属性）
	...

1、localName：不带命名空间前缀的节点名称。
2、namespaceURI：命名空间 URI 或者（在未指定的情况下是）null。
3、prefix：命名空间前缀或者（在未指定的情况下是）null。

```javascript
<html xmls="http://www.w3.org/1999/xhtml">

<body>
	<s:svg xmlns:s="http://www.w3.org/2000/svg">
</body>

<html>

方法
 isDefaultNamespace(namespaceURI)：在指定的 namespaceURI 是当前节点的默认命名空间的情况下返回 true。
 lookupNamespaceURI(prefix)：返回给定 prefix 的命名空间。
 lookupPrefix(namespaceURI)：返回给定 namespaceURI 的前缀。
```
对于 html   
	localName和 tagName 是  html
	namespaceURI 是  http://www.w3.org/1999/xhtml
	prefix  是  null
对于 svg
	localName是  svg 
	tagName 是  s:svg
	namespaceURI 是  http://www.w3.org/2000/xhtml
	prefix  是  s

