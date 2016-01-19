#!/usr/bin/php
<!DOCTYPE html>
<html>
<head>
    <title></title>
    <link rel="stylesheet" type="text/css" href="css/styles.css">
</head>
<body>
    <p><?php echo "This is website generated with PHP" ?></p>
    <p>This Select component is generated dynamically</p>
    <select>
    <?php foreach(Array("Banana", "Apple", "Orange") as $index => $fruit): ?>
        <option value="<?php echo $index ?>"><?php echo $fruit ?></option>
    <?php endforeach; ?>
    </select>
</body>
</html>